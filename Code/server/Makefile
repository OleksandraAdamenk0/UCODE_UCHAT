NAME = uchat

CC = clang
FLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

SRCDIR = src
INCDIR = inc
OBJDIR = obj

SRCFILES = $(wildcard $(SRCDIR)/*.c)
OBJFILES = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCFILES))

all $(NAME):
	touch $(NAME)