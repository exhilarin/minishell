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
	src/executor/redirections/redir_funcs.c \
	src/executor/redirections/redir_builtin.c \
	src/builtins/cd.c \
	src/builtins/env.c \
	src/builtins/pwd.c \
	src/builtins/exit.c \
	src/builtins/echo.c \
	src/builtins/unset.c \
	src/builtins/export.c \
	src/utils/syntax.c \
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

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Colors
COLOR_RESET = \033[0m
COLOR_RED = \033[0;31m
COLOR_GREEN = \033[0;32m
COLOR_YELLOW = \033[0;33m
COLOR_BLACK = \033[0;30m
COLOR_BOLD_RED = \033[1;31m

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(READLINE) $(RL_INC) $(RL_LIB) -o $@
	@echo "$(COLOR_BLACK)@ DONE $(NAME) ✅$(COLOR_RESET)"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@


$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	@rm -rf $(BUILD_DIR)
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	@echo "$(COLOR_RED)@ Cleaned $(NAME)$(COLOR_RESET)"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@echo "$(COLOR_RED)@ Full Cleaned $(NAME)$(COLOR_RESET)"

re: fclean all

leak: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp ./minishell

.PHONY: all clean fclean re
