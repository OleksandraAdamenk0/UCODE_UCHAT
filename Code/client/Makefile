NAME := uchat

CC := clang
FLAGS := -std=c11 -Wall -Wextra -Werror -Wpedantic

SRCDIR := src
INCDIR := inc
OBJDIR := obj

# LIBS
LIBS_DIR := libs
# ==============================================================================
# LIBMX
LIBMX_DIR = $(LIBS_DIR)/libmx
LIBMX_INCDIR = $(LIBMX_DIR)/inc
LIBMX = $(LIBMX_DIR)/libmx.a

# LOGGER
LOGGER_DIR := $(LIBS_DIR)/logger
LOGGER_INCDIR := $(LOGGER_DIR)/inc
LOGGER := $(LOGGER_DIR)/liblogger.a

SQLITE_DIR = $(LIBS_DIR)/sqlite
SQLITE_INCDIR = $(SQLITE_DIR)/inc
SQLITE = $(SQLITE_DIR)/sqlite.a

# ==============================================================================

SRCFILES = $(wildcard $(SRCDIR)/**/*.c) $(SRCDIR)/main.c
OBJFILES = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCFILES))

all: $(NAME)

$(NAME): $(LIBMX) $(LOGGER) $(SQLITE) $(OBJFILES)
	@$(CC) $(OBJFILES) -o $(NAME) -I $(INCDIR) -I $(LOGGER_INCDIR) -L$(LOGGER_DIR) -llogger -I $(LIBMX_INCDIR) -L$(LIBMX_DIR) -lmx -I $(SQLITE_INCDIR) -L$(SQLITE_DIR) -lsqlite3
$(OBJDIR)/%.o: $(SRCDIR)/%.c  | $(OBJDIR)
	@$(CC) $(FLAGS) -c -I $(INCDIR) -I $(LIBMX_INCDIR) $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(LIBMX):
	@$(MAKE) -C $(LIBMX_DIR)

$(LOGGER):
	@$(MAKE) -C $(LOGGER_DIR)

$(SQLITE):
	@$(MAKE) -C $(SQLITE_DIR)

uninstall: clean
	@if [ -f $(NAME) ]; then rm $(NAME); fi
	@$(MAKE) uninstall -C $(LIBMX_DIR)
	@$(MAKE) uninstall -C $(LOGGER_DIR)
	@$(MAKE) uninstall -C $(SQLITE_DIR)


clean:
	@rm -rf $(OBJDIR)
	@$(MAKE) clean -C $(LIBMX_DIR)
	@$(MAKE) clean -C $(LOGGER_DIR)
	@$(MAKE) clean -C $(SQLITE_DIR)

reinstall: uninstall all

.PHONY: all clean uninstall reinstall
