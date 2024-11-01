NAME = uchat

CC = clang
FLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

SRCDIR = src
INCDIR = inc
OBJDIR = obj

# LIBS
# ==============================================================================
# LIBMX
LIBMX_DIR = libmx
LIBMX_INCDIR = $(LIBDIR)/inc
LIBMX_MAKEFILE = $(LIBMX_DIR)/Makefile
LIBMX = $(LIBMX_DIR)/libmx.a

# ==============================================================================

MODULES = $(SRCDIR)/json_handler $(SRCDIR)/gui $(SRCDIR)/cache $(SRCDIR)/security

SRCFILES = $(wildcard $(SRCDIR)/**/*.c) $(SRCDIR)/main.c
OBJFILES = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCFILES))

all: $(NAME)

$(NAME): $(LIBMX) $(OBJFILES)
	$(CC) $(OBJFILES) -o $(NAME) -Llibmx -lmx

$(OBJDIR)/%.o: $(SRCDIR)/%.c  | $(OBJDIR)
	$(CC) $(FLAGS) -c -I $(INCDIR) -I $(LIBMX_INCDIR) $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(LIBMX):
	@$(MAKE) -C $(LIBMX_DIR)

uninstall: clean
	@if [ -f $(NAME) ]; then rm $(NAME); fi
	@$(MAKE) uninstall -C $(LIBMX_DIR)

clean:
	rm -rf $(OBJDIR)
	@$(MAKE) clean -C $(LIBMX_DIR)

reinstall: uninstall all

.PHONY: all clean uninstall reinstall
