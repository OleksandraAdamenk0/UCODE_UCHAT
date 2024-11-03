//
// Created by aleksa on 11/2/24.
//

#include "logger.h"

#define MAX_LOG_SIZE 1024 * 1024
#define LOG_DIR "logs/"
#define LOG_FILENAME "log.log"
#define ROTATED_LOG_FILENAME_FORMAT "log_%Y-%m-%d_%H-%M-%S.log"

typedef enum e_LVL {DEBUG, INFO, WARN, ERROR, FATAL} t_LVL;

static struct s_config {
    t_LVL level;
    int log_file;
    char *log_file_path;
    char *log_dir;
    pthread_mutex_t lock;
    int current_size;
    int max_size;
    bool is_initialized;
} config = {DEBUG, 0, NULL, NULL, PTHREAD_MUTEX_INITIALIZER, 0, 0, false};

static int rotate_log_file() {
    if (config.log_file != -1) close(config.log_file);

    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    char rotated_filename[256];
    strftime(rotated_filename, sizeof(rotated_filename), ROTATED_LOG_FILENAME_FORMAT, tm_info);
	char *temp = mx_strdup(config.log_dir);
    char *new_name = mx_strjoin(temp, rotated_filename);
    free(temp);
    if (rename(config.log_file_path, new_name) != 0) {
        free(new_name);
        return -1;
    }
    free(new_name);

    config.log_file = open(config.log_file_path, O_CREAT | O_TRUNC | O_WRONLY, 0600);
    if (config.log_file < 0) return -2;

    return 0;
}

static char *add_timestamp(const char *msg) {
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    char timestamp[64];
    strftime(timestamp, sizeof(timestamp), "[%Y-%m-%d %H:%M:%S] ", tm_info);

    char *final_msg = mx_strjoin(timestamp, msg);
    return final_msg;
}

static int write_msg(char *msg, t_LVL lvl) {
    pthread_mutex_lock(&config.lock);

    struct stat st;
    if (stat(config.log_file_path, &st) == 0 && st.st_size >= config.max_size) {
        if (rotate_log_file() < 0) {
            pthread_mutex_unlock(&config.lock);
            return -1;
        }
    }

    char *timestamped_msg = add_timestamp(msg);
    if (!timestamped_msg) {
        pthread_mutex_unlock(&config.lock);
        return -2;
    }

    write(config.log_file, timestamped_msg, mx_strlen(timestamped_msg));
    pthread_mutex_unlock(&config.lock);
    return 0;
}

static int create_dir(char *path) {
    struct stat st = {0};
    if (stat(path, &st) == -1)
        if (mkdir(path, 0777) != 0 && errno != EEXIST) return -1;
	return 0;
}

static int create_log_directory(const char *path) {
    char **path_array = mx_strsplit(path, '/');
    int part_amount = mx_count_substr(path, "/") + 1;
    char *path_to_dir = mx_strnew(0);

    for (int i = 0; i < part_amount - 1; i++) {
        if (i != 0) path_to_dir = mx_strjoin(path_to_dir, "/");
        path_to_dir = mx_strjoin(path_to_dir, path_array[i]);
        if (create_dir(path_to_dir) < 0) return -1;
    }
    for (int i = 0; i < part_amount; i++) free(path_array[i]);
    free(path_array);
    return 0;
}

static int parse_config_file(char *config_path) {
    FILE *config_file = fopen(config_path, "r");
    if (!config_file) return -1;

    char *line = NULL;
    size_t len = 0;

    char *dir = NULL;
    char *filename = NULL;

    while (getline(&line, &len, config_file) != -1) {
        if (line[0] == '#' || mx_isspace((unsigned char)line[0])) continue;

        int delimiter = mx_get_char_index(line, '=');
        if (delimiter < 1) continue;

        char *value = mx_strtrim(line + delimiter + 1);

        char *key = mx_strndup(line, delimiter);
        key = mx_strtrim(key);

        if (mx_strcmp(key, "path") == 0) {
            dir = mx_strdup(value);
        } else if (mx_strcmp(key, "file_name") == 0) {
            filename = mx_strdup(value);
        } else if (mx_strcmp(key, "max_log_size") == 0) {
            config.max_size = mx_atoi(value);
        } else if (mx_strcmp(key, "log_level") == 0) {
            if (mx_strcmp(value, "DEBUG") == 0) config.level = DEBUG;
            else if (mx_strcmp(value, "INFO") == 0) config.level = INFO;
            else if (mx_strcmp(value, "WARN") == 0) config.level = WARN;
            else if (mx_strcmp(value, "ERROR") == 0) config.level = ERROR;
            else if (mx_strcmp(value, "FATAL") == 0) config.level = FATAL;
        }

        free(value);
        free(key);
    }

    if (!dir) dir = mx_strdup(LOG_DIR);
    config.log_dir = mx_strdup(dir);
    if (!filename) filename = mx_strdup(LOG_FILENAME);
    create_log_directory(dir);
    config.log_file_path = mx_strjoin(dir, filename);

    free(dir);
    free(filename);

    free(line);
    fclose(config_file);
    return 0;
}

int logger_init(char *config_path) {
    if (config.is_initialized) return 0;

    if (parse_config_file(config_path) < 0) return -1;

    if (config.log_file_path == NULL || mx_strlen(config.log_file_path) < 1)
        config.log_file_path = LOG_FILENAME;

    if (config.max_size < 1) config.max_size = MAX_LOG_SIZE;

    config.log_file = open(config.log_file_path, O_CREAT | O_APPEND | O_WRONLY, 0600);
    if (config.log_file < 0) return -3;

    pthread_mutex_init(&config.lock, NULL);

    config.is_initialized = true;
    return 0;
}

int logger_debug(char *msg) {
    char *full_msg = mx_strjoin("[DEBUG] ", msg);
    if (write_msg(full_msg, DEBUG) < 0) {
        free(full_msg);
      	return -1;
	}
    free(full_msg);
    return 0;
}

int logger_info(char *msg) {
    char *full_msg = mx_strjoin("[INFO] ", msg);
    if (write_msg(full_msg, INFO) < 0) {
        free(full_msg);
        return -1;
    }
    free(full_msg);
    return 0;
}

int logger_warn(char *msg) {
    char *full_msg = mx_strjoin("[WARN] ", msg);
    if (write_msg(full_msg, WARN) < 0)  {
        free(full_msg);
        return -1;
    }
    free(full_msg);
    return 0;
}

int logger_error(char *msg) {
    char *full_msg = mx_strjoin("[ERROR] ", msg);
    if (write_msg(full_msg, ERROR) < 0)  {
        free(full_msg);
        return -1;
    }
    free(full_msg);
    return 0;
}

int logger_fatal(char *msg) {
    char *full_msg = mx_strjoin("[FATAL] ", msg);
    if (write_msg(full_msg, FATAL) < 0)  {
        free(full_msg);
        return -1;
    }
    free(full_msg);
    return 0;
}

void logger_close() {
    if (config.log_file) close(config.log_file);
    free(config.log_file_path);
    pthread_mutex_destroy(&config.lock);
}
