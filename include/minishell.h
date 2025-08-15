/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:19:03 by iguney            #+#    #+#             */
/*   Updated: 2025/08/15 06:40:30 by iguney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "lexer.h"
# include "parser.h"
# include "executor.h"
# include "builtins.h"
# include "../libft/libft.h"

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>

extern volatile sig_atomic_t	g_signal;

typedef struct s_shell
{
	char	*input;
	t_env	*env;
	t_exec	*exec;
	t_token	*token_list;
	t_cmd	*command_list;
	int		exit_status;
}	t_shell;

void	signal_handler(int sig);
void	process(t_shell *shell);
int		shutdown_shell(t_shell *shell);

void	init_signal(void);
void	init_shell(t_shell *shell);
void	init_env(t_shell *shell, char **envp);
t_cmd	*init_cmd(void);
t_exec	*init_exec(void);

int		free_all(t_shell *shell);
void	free_tokens(t_token *tokens);
void	free_cmd(t_cmd	*commands);
void	free_redir(t_redir *redir);
void	free_env(t_env *env);

#endif