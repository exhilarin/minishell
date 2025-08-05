/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:19:20 by iguney            #+#    #+#             */
/*   Updated: 2025/08/05 15:58:05 by iguney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <sys/wait.h>
# include <sys/types.h>

typedef struct s_shell	t_shell;

int		executor(t_shell *shell, t_cmd *cmds);
void	child_process(t_shell *shell, int in_fd, int fd[2]);

int		is_builtin(t_cmd *cmd);
int		exec_builtin(t_shell *shell);
int		builtin_needs_parent(char *name);
void	parent_process(t_cmd *cmds, int in_fd, int *fd, pid_t pid);

// void	is_redir_heredoc(t_redir *redir, t_cmd *cmds);

#endif