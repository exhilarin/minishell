/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:19:20 by iguney            #+#    #+#             */
/*   Updated: 2025/08/05 00:52:51 by iguney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <sys/wait.h>
# include <sys/types.h>

int		executor(t_cmd *cmds);
void	child_process(t_cmd *cmd, int in_fd, int fd[2]);

int		is_builtin(t_cmd *cmd);
int		exec_builtin(t_cmd *cmd);
int		builtin_needs_parent(char *name);
void	parent_process(t_cmd *cmds, int in_fd, int *fd, pid_t pid);

// void	is_redir_heredoc(t_redir *redir, t_cmd *cmds);

#endif