//
// Created by oleksandra on 17/11/24.
//

#include "client.h"
#include "connection.h"
#include "gui.h"

int fd;
int mode;

static int create_socket() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) return -1;
    return sockfd;
}

static struct sockaddr_in create_address() {
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    return addr;
}

static int setup_non_blocking_mode(int sockfd) {
    int flags = fcntl(sockfd, F_GETFL, 0);
    if (flags == -1) return -1;
    if (fcntl(sockfd, F_SETFL, flags | O_NONBLOCK) == -1) return -1;
    return 0;
}

static int setup_blocking_mode(int sockfd) {
    int flags = fcntl(sockfd, F_GETFL, 0);
    if (flags == -1) {
        logger_error("Failed to get socket flags\n");
        return -1;
    }

    flags &= ~O_NONBLOCK;
    if (fcntl(sockfd, F_SETFL, flags) == -1) {
        logger_error("Failed to set socket to blocking mode\n");
        return -1;
    }

    logger_debug("Socket is set to blocking mode\n");
    return 0;
}

static int check_time_out(int sockfd) {
    fd_set writefds;
    struct timeval tv;
    FD_ZERO(&writefds);
    FD_SET(sockfd, &writefds);
    tv.tv_sec = 10;
    tv.tv_usec = 0;
    return select(sockfd + 1, NULL, &writefds, NULL, &tv);
}

static int usual_connect(int sockfd, struct sockaddr_in server_addr) {
    logger_warn("Failed to set non-blocking mode, "
                "falling back to blocking connect\n");
    if (connect(sockfd, (struct sockaddr *)&server_addr,
                sizeof(server_addr)) < 0) {
        logger_fatal("Failed to connect in blocking mode\n");
        return -1;
    }
    return 0;
}

static int connection(int sockfd) {
    struct sockaddr_in server_addr = create_address();
    if (inet_pton(AF_INET, ip, &server_addr.sin_addr) <= 0)
        return -1;

    // set up non-blocking mode to get control back to the program
    // without waiting for connect to be executed
    if (setup_non_blocking_mode(sockfd) < 0)
        return usual_connect(sockfd, server_addr);

    struct timeval start_time, current_time;
    gettimeofday(&start_time, NULL);

    while (1) {
        if (connect(sockfd, (struct sockaddr *) &server_addr,
                    sizeof(server_addr)) == 0) {
            logger_info("Connected successfully\n");
            break; // Успешное подключение
        }
        if (errno == EINPROGRESS) {
            struct timeval tv;
            tv.tv_sec = 0;
            tv.tv_usec = 500000;

            fd_set writefds;
            FD_ZERO(&writefds);
            FD_SET(sockfd, &writefds);

            int result = select(sockfd + 1, NULL, &writefds, NULL, &tv);
            if (result > 0) {
                int error = 0;
                socklen_t len = sizeof(error);
                if (getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &error, &len) < 0) {
                    logger_fatal("getsockopt failed\n");
                    if (setup_blocking_mode(sockfd) < 0)
                        logger_warn("Failed to restore blocking mode\n");
                }
                if (error == 0) {
                    logger_info("Connected successfully\n");
                    break; // Подключение успешно
                }
                char *msg = mx_strjoin("Connection failed during select: ", strerror(errno));
                logger_warn(msg);
                free(msg);
            }
        } else if (errno == ECONNREFUSED) {
            logger_warn("Connection refused, retrying...\n");
        } else {
            char *msg = mx_strjoin("Unexpected connection error: ", strerror(errno));
            logger_fatal(msg);
            free(msg);
            if (setup_blocking_mode(sockfd) < 0)
                logger_warn("Failed to restore blocking mode\n");
        }
        gettimeofday(&current_time, NULL);
        long elapsed_time = (current_time.tv_sec - start_time.tv_sec) * 1000 +
                            (current_time.tv_usec - start_time.tv_usec) / 1000;
        if (elapsed_time >= 10000) { // 10 секунд
            logger_warn("Connection attempt timed out\n");
            if (setup_blocking_mode(sockfd) < 0)
                logger_warn("Failed to restore blocking mode\n");
            return -2;
        }
        usleep(500000); // Ждем перед новой попыткой
    }

    if (setup_blocking_mode(sockfd) < 0) {
        logger_warn("Failed to restore blocking mode\n");
    }
    return 0;
}

static int open_connection() {
    fd = create_socket();
    if (fd < 0) {
        logger_error("error occurred while creating socket\n");
        return -1;
    } else logger_info("socket was created successfully\n");

    int status = connection(fd);
    if (status < 0){
        mx_close_connection();
        return status;
    }
    return fd;
}

void *mx_connection_thread(void *arg) {
    fd = open_connection();

    if (fd > 0) {
        mode = 0;
        logger_info("Connection succeeded. Running online mode\n");
        if (mx_db_init() < 0) {
            logger_error("DB initialization failed.\n");
            mode = -2;
        }
    } else if (mx_isdb_valid()) {
        mode = -1;
        logger_error("Connection failed. Running offline mode\n");
    } else {
        mode = -2;
        logger_error("Connection failed. Local DB unavailable.\n");
    }

    if (mode == -2) {
        webkit_web_view_run_javascript(webview, "goToError();", NULL, NULL, NULL);
    } else {
        webkit_web_view_run_javascript(webview, "goToLogin();", NULL, NULL, NULL);

    }
    return NULL;
}
