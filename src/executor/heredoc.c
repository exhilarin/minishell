/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 06:51:59 by mugenan           #+#    #+#             */
/*   Updated: 2025/08/26 02:22:32 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_child(t_redir *redir, int wfd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, redir->file) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, wfd);
		free(line);
	}
	close(wfd);
	exit_shell(0, NULL);
}

static int	redir_heredoc_parent(t_shell *shell, int fd[2], pid_t pid)
{
	int	status;

	close(fd[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	else if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		return (WEXITSTATUS(status));
	shell->heredoc_fd = fd[0];
	return (0);
}

int	redir_heredoc(t_shell *shell, t_redir *redir)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		exit_shell(1, "minishell: pipe failed\n");
	discard_signals();
	g_signal_code = 2;
	pid = fork();
	if (pid == -1)
	{
		close(fd[0]);
		close(fd[1]);
		exit_shell(1, "minishell: fork failed\n");
	}
	if (pid == 0)
	{
		close(fd[0]);
		init_signal();
		heredoc_child(redir, fd[1]);
	}
	close(fd[1]);
	return (redir_heredoc_parent(shell, fd, pid));
}

