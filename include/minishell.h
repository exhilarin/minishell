#ifndef MINISHELL_H
# define MINSHELL_H

# include "lexer.h"
# include "parser.h"
# include "executor.h"
# include "../libft/libft.h"

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

void		print_tokens(t_token *tokens);
char		*prompt(void);
int			has_unclosed_quotes(const char *input);
const char	*token_type_to_str(t_token_type type);


#endif