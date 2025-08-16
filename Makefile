NAME        = minishell

SRC_DIR     = src
BUILD_DIR   = build
INCLUDE_DIR = include
LIBFT_DIR   = libft

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -I$(INCLUDE_DIR) -I$(LIBFT_DIR) -g

READLINE    = -lreadline
RL_INC      = -I/usr/include
RL_LIB      = -L/usr/lib
LIBFT       = $(LIBFT_DIR)/libft.a

SRCS = \
	src/main.c \
	src/utils/init.c \
	src/utils/signal.c \
	src/lexer/lexer.c \
	src/parser/parser.c \
	src/parser/expand.c \
	src/executor/heredoc.c \
	src/executor/executor.c \
	src/executor/builtins.c \
	src/executor/environment.c \
	src/executor/redirections.c \
	src/builtins/echo.c \
	src/builtins/exit.c \
	src/builtins/env.c \
	src/utils/error.c \
	src/utils/tools.c \
	src/utils/free.c \
	src/utils/add.c \
	# src/builtins/cd.c \
	# src/builtins/export.c \
	# src/builtins/pwd.c \
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

leak:all
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp ./minishell

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "🧹 Executable removed."

re: fclean all

.PHONY: all clean fclean re
