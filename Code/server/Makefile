NAME := uchat_server

CC := clang
СFLAGS := -std=c11 -Wall -Wextra -Werror -Wpedantic

SRCDIR := src
INCDIR := inc
OBJDIR := obj

# LIBS
LIBS_DIR := libs
# ==============================================================================
# LIBMX
LIBMX_DIR := $(LIBS_DIR)/libmx
LIBMX_INCDIR := $(LIBMX_DIR)/inc
LIBMX := $(LIBMX_DIR)/libmx.a

# LOGGER
LOGGER_DIR := $(LIBS_DIR)/logger
LOGGER_INCDIR := $(LOGGER_DIR)/inc
LOGGER := $(LOGGER_DIR)/liblogger.a

# CJSON
CJSON_DIR := $(LIBS_DIR)/cjson
CJSON_INCDIR := $(CJSON_DIR)/inc
CJSON := $(CJSON_DIR)/libcjson.a

# SQLITE

SQLITE_DIR := $(LIBS_DIR)/sqlite
SQLITE_INCDIR := $(SQLITE_DIR)/inc
SQLITE := $(SQLITE_DIR)/libsqlite.a

# BASE64
BASE64_DIR := $(LIBS_DIR)/base64
BASE64_INCDIR := $(BASE64_DIR)/inc
BASE64 := $(BASE64_DIR)/libbase64.a

# ==============================================================================

SRCFILES = $(shell find $(SRCDIR) -name "*.c")
OBJFILES = $(patsubst %.c, $(OBJDIR)/%.o, $(notdir $(SRCFILES)))

all: $(NAME)

$(NAME): $(LIBMX) $(LOGGER) $(CJSON) $(BASE64) $(OBJFILES)

	@$(CC) $(OBJFILES) -o $(NAME) -I $(INCDIR) -pthread -I $(LOGGER_INCDIR) -L$(LOGGER_DIR) -llogger -I $(LIBMX_INCDIR) -L$(LIBMX_DIR) -lmx -I $(CJSON_INCDIR) -L$(CJSON_DIR) -lcjson -I $(BASE64_INCDIR) -L$(BASE64_DIR) -lbase64 -I $(SQLITE_INCDIR) -L$(SQLITE_DIR) -lsqlite3

$(OBJDIR)/%.o: $(SRCDIR)/%.c  | $(OBJDIR)
	@$(CC) $(CFLAGS) -c -I $(INCDIR) -I $(LIBMX_INCDIR) -I $(LOGGER_INCDIR) -I $(CJSON_INCDIR) -I $(BASE64_INCDIR) $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/*/%.c  | $(OBJDIR)
	@$(CC) $(CFLAGS) -c -I $(INCDIR) -I $(LIBMX_INCDIR) -I $(LOGGER_INCDIR) -I $(CJSON_INCDIR) -I $(BASE64_INCDIR) $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(LIBMX):
	@$(MAKE) -C $(LIBMX_DIR)

$(LOGGER):
	@$(MAKE) -C $(LOGGER_DIR)

$(CJSON):
	@$(MAKE) -C $(CJSON_DIR)

$(BASE64):
	@$(MAKE) -C $(BASE64_DIR)

$(SQLITE):
	@$(MAKE) -C $(SQLITE_DIR)

uninstall: clean
	@if [ -f $(NAME) ]; then rm $(NAME); fi
	@$(MAKE) uninstall -C $(LIBMX_DIR)
	@$(MAKE) uninstall -C $(LOGGER_DIR)
	@$(MAKE) uninstall -C $(CJSON_DIR)
	@$(MAKE) uninstall -C $(BASE64_DIR)
	@$(MAKE) uninstall -C $(SQLITE_DIR)

clean:
	@rm -rf $(OBJDIR)
	@$(MAKE) clean -C $(LIBMX_DIR)
	@$(MAKE) clean -C $(LOGGER_DIR)
	@$(MAKE) clean -C $(CJSON_DIR)
	@$(MAKE) clean -C $(BASE64_DIR)
	@$(MAKE) clean -C $(SQLITE_DIR)

reinstall: uninstall all

.PHONY: all clean uninstall reinstall
