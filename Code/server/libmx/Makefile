NAME = libmx.a

CC = clang
FLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

SRCDIR = src
INCDIR = inc
OBJDIR = obj

SRCFILES = $(wildcard $(SRCDIR)/*.c)
OBJFILES = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCFILES))

all: $(NAME)

$(NAME): $(OBJFILES)
	ar rcs $(NAME) $(OBJFILES)

$(OBJDIR)/%.o: $(SRCDIR)/%.c  | $(OBJDIR)
	$(CC) $(FLAGS) -I $(INCDIR) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

uninstall:
	rm -rf $(OBJDIR) $(NAME)

clean:
	rm -rf $(OBJDIR)

reinstall: uninstall all

.PHONY: all clean uninstall reinstall
