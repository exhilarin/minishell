NAME        = minishell

SRC_DIR     = src
BUILD_DIR   = build
INCLUDE_DIR = include
LIBFT_DIR   = libft

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -I$(INCLUDE_DIR) -I$(LIBFT_DIR)

READLINE    = -lreadline
RL_INC      = -I/usr/include
RL_LIB      = -L/usr/lib
LIBFT       = $(LIBFT_DIR)/libft.a

SRCS = \
	src/main.c \
	src/lexer/lexer.c \
	src/lexer/utils.c \
	src/parser/parser.c \
	# src/executor/executor.c \
	# src/builtins/echo.c \
	# src/builtins/cd.c \
	# src/builtins/pwd.c \
	# src/builtins/env.c \
	# src/builtins/export.c \
	# src/builtins/unset.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(READLINE) $(RL_INC) $(RL_LIB) -o $@
	@echo "✅ Build completed."

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	@rm -rf $(BUILD_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "🧹 Object files cleaned."

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "🧹 Executable removed."

re: fclean all

.PHONY: all clean fclean re
