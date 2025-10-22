/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 06:51:59 by mugenan           #+#    #+#             */
/*   Updated: 2025/08/28 07:53:47 by mugenan          ###   ########.fr       */
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
	int	exit_code;

	close(fd[1]);
	waitpid(pid, &status, 0);
	exit_code = 0;
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			ft_putendl_fd("Quit (core dumped)", STDERR_FILENO);
		exit_code = 128 + WTERMSIG(status);
	}
	else if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	if (exit_code != 0)
	{
		close(fd[0]);
		shell->heredoc_fd = -1;
		exit_status_manager(exit_code, 1);
		return (exit_code);
	}
	shell->heredoc_fd = fd[0];
	return (exit_code);
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
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, sigquit_handler);
		heredoc_child(redir, fd[1]);
	}
	close(fd[1]);
	return (redir_heredoc_parent(shell, fd, pid));
}

int	handle_heredoc(t_shell *shell, t_redir *redir)
{
	while (redir)
	{
		if (redir->type == HEREDOC && redir_heredoc(shell, redir))
			return (1);
		redir = redir->next;
	}
	return (0);
}
