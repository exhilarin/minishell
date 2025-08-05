/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:19:03 by iguney            #+#    #+#             */
/*   Updated: 2025/08/05 03:57:31 by iguney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "lexer.h"
# include "parser.h"
# include "executor.h"
# include "builtins.h"
# include "../libft/libft.h"

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_shell
{
	char	*input;
	t_token	*token_list;
	t_cmd	*command_list;
	int		exit_status;
}	t_shell;

char	*prompt(void);
void	process(t_shell *shell);
int		shutdown_shell(t_shell *shell);
int		has_unclosed_quotes(const char *input);

#endif