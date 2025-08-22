/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:19:20 by iguney            #+#    #+#             */
/*   Updated: 2025/08/23 01:39:25 by ilyas-guney      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <sys/types.h>

typedef struct s_shell	t_shell;

typedef struct s_exec
{
	char	*cmd_path;
	char	**paths;
	char	**envp;
}	t_exec;

void	expand_all(t_shell *shell);
void	expand_args(t_shell *shell, t_cmd *cmd);
void	expand_redirs(t_shell *shell, t_cmd *cmd);
char	*expand_string(t_shell *shell, char *str, int quote);
char	*expand_var(t_shell *shell, char *str, int *i);

void	executor(t_shell *shell, t_cmd *cmd);
void	exec_command(t_shell *shell, t_cmd *cmd);
void	child_process(t_shell *shell, t_cmd *cmd, int fd[2]);
void	parent_process(t_shell *shell, t_cmd *cmd, int fd[2], pid_t pid);

char	*get_cmd_path(t_shell *shell, t_cmd *cmd);
int		check_special_case(t_shell *shell, t_cmd *cmd, t_redir *redir);

void	exec_builtin_with_redir(t_shell *shell, t_cmd *cmd);
void	redir_heredoc(t_shell *shell, t_redir *redir);
void	handle_heredoc(t_shell *shell, t_redir *redir);
void	handle_redirections(t_shell *shell, t_redir *redir, int proccess);

#endif