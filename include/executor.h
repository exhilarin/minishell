/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:19:20 by iguney            #+#    #+#             */
/*   Updated: 2025/08/07 04:40:24 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <sys/wait.h>
# include <sys/types.h>

typedef struct s_shell	t_shell;

typedef struct s_exec
{
	char	*cmd_path;
    char    **paths;
	char	**envp;
}	t_exec;

void    child_process(t_shell *shell, int in_fd, int fd[2]);
void    parent_process(t_cmd *cmds, int *in_fd, int *fd, pid_t pid);

int		is_builtin(t_cmd *cmd);
int		exec_builtin(t_shell *shell);
int		builtin_needs_parent(char *name);

int		executor(t_shell *shell);
void	exec_command(t_shell *shell);
char	*get_cmd_path(t_shell *shell);
// void	is_redir_heredoc(t_redir *redir, t_cmd *cmds);

#endif