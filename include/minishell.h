/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:19:03 by iguney            #+#    #+#             */
/*   Updated: 2025/08/28 04:04:04 by iguney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "lexer.h"
# include "parser.h"
# include "expand.h"
# include "executor.h"
# include "builtins.h"
# include "../libft/libft.h"

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>

extern int	g_signal_code;

typedef struct s_shell
{
	char	*input;
	t_env	*env;
	t_exec	*exec;
	t_token	*token_list;
	t_cmd	*command_list;
	int		heredoc_fd;
	int		in_fd;
}	t_shell;

t_cmd	*init_cmd(void);
t_exec	*init_exec(void);
t_env	*init_env_node(void);
t_shell	*set_get_shell(t_shell *sh);
void	init_shell(t_shell *shell);
void	init_env(t_shell *shell, char **envp);

int		shutdown_shell(t_shell *shell);
int		exit_status_manager(int status, int mode);

void	process(t_shell *shell);

void	exit_shell(int code, char *msg);
void	print_error(char *msg, int code);
void	exec_error(t_shell *shell, t_cmd *cmd);

void	handle_no_cmd_path(t_cmd *cmd);
void	handle_flag_error(t_cmd *cmd);
void	handle_access_error(t_shell *shell, t_cmd *cmd);

void	init_signal(void);
void	discard_signals(void);
void	wait_and_set_status(pid_t *pids, int count);

void	add_cmd_to_lst(t_cmd **cmds, t_cmd *new_cmd);
void	add_redir_to_cmd(t_cmd *cmd, int type, char *file);
void	add_arg_to_cmd(t_cmd *current_cmd, char *token_value);
void	add_token(t_token **tokens, t_token_type type, char *value);
char	**add_argv(char **old_argv, char *token_value, int argc);

int		free_all(t_shell *shell);
void	free_env(t_env *env);
void	free_envp(char **envp);
void	free_exec(t_exec *exec);
void	free_cmd(t_cmd	*commands);
void	free_redir(t_redir *redir);
void	free_tokens(t_token *tokens);
void	free_char_array(char **array);
void	free_argv(char **new_argv, int i);

#endif