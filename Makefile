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
	src/lexer/tokenizer.c \
	src/parser/parser.c \
	src/parser/expand/expand.c \
	src/parser/expand/handle.c \
	src/parser/expand/expand_utils.c \
	src/executor/heredoc.c \
	src/executor/executor.c \
	src/executor/builtins.c \
	src/executor/environment.c \
	src/executor/redirections/redir_builtin.c \
	src/executor/redirections/redir_funcs.c \
	src/builtins/cd.c \
	src/builtins/env.c \
	src/builtins/pwd.c \
	src/builtins/exit.c \
	src/builtins/echo.c \
	src/builtins/unset.c \
	src/builtins/export.c \
	src/utils/add/add_cmd.c \
	src/utils/add/add_token.c \
	src/utils/free/free_funcs.c \
	src/utils/free/free_shell.c \
	src/utils/error/exit_error.c \
	src/utils/error/handle_error.c \
	src/utils/tools/env_tools.c \
	src/utils/tools/func_tools.c \
	src/utils/tools/quote_tools.c \
	src/utils/tools/export_tools.c \
	src/utils/syntax.c \

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
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp ./minishell

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "🧹 Executable removed."

re: fclean all

.PHONY: all clean fclean re
