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

# ==============================================================================

SRCFILES = $(wildcard $(SRCDIR)/**/*.c) $(SRCDIR)/main.c
OBJFILES = $(patsubst $(SRCDIR)/%/%.c, $(OBJDIR)/%.o, $(SRCFILES))

all: $(NAME)

$(NAME): $(LIBMX) $(LOGGER) $(OBJFILES)
	@$(CC) $(OBJFILES) -o $(NAME) -I $(INCDIR) -I $(LOGGER_INCDIR) -L$(LOGGER_DIR) -llogger -I $(LIBMX_INCDIR) -L$(LIBMX_DIR) -lmx

$(OBJDIR)/%.o: $(SRCDIR)/%.c  | $(OBJDIR)
	@$(CC) $(СFLAGS) -c -I $(INCDIR) -I $(LIBMX_INCDIR) -I $(LOGGER_INCDIR) $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(LIBMX):
	@$(MAKE) -C $(LIBMX_DIR)

$(LOGGER):
	@$(MAKE) -C $(LOGGER_DIR)

uninstall: clean
	@if [ -f $(NAME) ]; then rm $(NAME); fi
	@$(MAKE) uninstall -C $(LIBMX_DIR)
	@$(MAKE) uninstall -C $(LOGGER_DIR)

clean:
	@rm -rf $(OBJDIR)
	@$(MAKE) clean -C $(LIBMX_DIR)
	@$(MAKE) clean -C $(LOGGER_DIR)

reinstall: uninstall all

.PHONY: all clean uninstall reinstall
