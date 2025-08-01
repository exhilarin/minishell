# ifndef MINISHELL_H
# define MINISHELL_H

# include "lexer.h"
# include "parser.h"
# include "executor.h"
# include "../libft/libft.h"

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>

char		*prompt(void);
void        process(char *input);
int			has_unclosed_quotes(const char *input);

#endif