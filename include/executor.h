/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:19:20 by iguney            #+#    #+#             */
/*   Updated: 2025/08/14 23:57:00 by iguney           ###   ########.fr       */
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

void	expand(t_shell *shell);
void	expand_args(t_shell *shell, t_cmd *cmd);
void	expand_redirs(t_shell *shell, t_cmd *cmd);
char	*expand_string(t_shell *shell, char *str, int quote);
char	*expand_var(t_shell *shell, char *str, int *i);

void	child_process(t_shell *shell, int in_fd, int fd[2]);
void	parent_process(t_cmd *cmds, int *in_fd, int *fd, pid_t pid);

int		executor(t_shell *shell);
void	exec_command(t_shell *shell);
char	*get_cmd_path(t_shell *shell);

int		exec_builtin_with_redir(t_shell *shell);
void	handle_redirections(t_shell *shell, t_redir *redir);

#endif