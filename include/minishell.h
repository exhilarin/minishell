/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:19:03 by iguney            #+#    #+#             */
/*   Updated: 2025/08/18 18:41:17 by mugenan          ###   ########.fr       */
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
	int		heredoc_fd;
	int		in_fd;
}	t_shell;

void	signal_handler(int sig);
void	process(t_shell *shell);
int		shutdown_shell(t_shell *shell);

void	init_signal(void);
void	init_shell(t_shell *shell);
void	init_env(t_shell *shell, char **envp);
t_cmd	*init_cmd(void);
t_exec	*init_exec(void);

void	add_token(t_token **tokens, t_token_type type, char *value);
void	add_arg_to_cmd(t_cmd *current_cmd, char *token_value);
void	add_redir_to_cmd(t_cmd *cmd, int type, char *file);
void	add_cmd_to_lst(t_cmd **cmds, t_cmd *new_cmd);
char	**add_argv(char **old_argv, char *token_value, int argc);

int		free_all(t_shell *shell);
void	free_tokens(t_token *tokens);
void	free_cmd(t_cmd	*commands);
void	free_redir(t_redir *redir);
void	free_env(t_env *env);
void	free_exec(t_exec *exec);
void	free_argv(char **new_argv, int i);

#endif