/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 23:21:21 by mugenan           #+#    #+#             */
/*   Updated: 2025/08/05 20:10:37 by iguney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	executor(t_shell *shell, t_cmd *cmds)
{
	int		fd[2];
	int		in_fd;
	// pid_t	pid;

	in_fd = 0;
	if (cmds && !cmds->next && is_builtin(cmds))
		// && builtin_needs_parent(cmds->argv[0]))
		return (exec_builtin(shell));
	while (cmds)
	{
		// is_redir_heredoc(cmds->redir, cmds);
		if (cmds->next && pipe(fd) == -1)
			return (perror("pipe"), 1);
		// pid = fork();
		// if (pid == -1)
		// 	return (perror("fork"), 1);
		// if (pid == 0)
		// 	child_process(shell, in_fd, fd);
		// parent_process(cmds, in_fd, fd, pid);
		cmds = cmds->next;
	}
	return (0);
}

void	child_process(t_shell *shell, int in_fd, int fd[2])
{
	if (in_fd != 0)
		dup2(in_fd, STDIN_FILENO);
	if (shell->command_list->next)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
	}
	close(fd[1]);
	//handle_redirections(shell->command_list->redir);
	if (!shell->command_list->argv || !shell->command_list->argv[0])
	{
		shell->exit_status = 0;
		exit(shutdown_shell(shell));
	}
	if (is_builtin(shell->command_list))
		exec_builtin(shell);
	// exec_command(shell->command_list);
}

void	parent_process(t_cmd *cmds, int in_fd, int *fd, pid_t pid)
{
	if (in_fd != 0)
		close(in_fd);
	if (cmds->next)
	{
		close(fd[1]);
		in_fd = fd[0];
	}
	waitpid(pid, NULL, 0);
}
