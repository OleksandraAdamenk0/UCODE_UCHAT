NAME := liblogger.a

CC := clang
СFLAGS := -std=c11 -Wall -Wextra -Werror -Wpedantic

SRC_DIR := src
OBJ_DIR := obj
INC_DIR := inc

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# LIBMX
LIBMX_DIR := libmx
LIBMX_INCDIR := $(LIBMX_DIR)/inc
LIBMX := $(LIBMX_DIR)/libmx.a

all: $(NAME)

$(NAME): $(LIBMX) $(OBJ)
	@ar rcs $@ $^

$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBMX_INCDIR) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBMX):
	@$(MAKE) -C $(LIBMX_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) clean -C $(LIBMX_DIR)

uninstall: clean
	@if [ -f $(NAME) ]; then rm $(NAME); fi
	@$(MAKE) uninstall -C $(LIBMX_DIR)

reinstall: uninstall all

.PHONY: all clean uninstall reinstall
