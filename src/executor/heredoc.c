/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 06:51:59 by mugenan           #+#    #+#             */
/*   Updated: 2025/08/24 23:55:24 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	exit_shell(130);
}

static void	heredoc_child(t_redir *redir, int wfd)
{
	char	*line;

	signal(SIGINT, heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
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
	exit_shell(0);
}

static int	heredoc_parent_wait(t_shell *sh, int fd[2], pid_t pid)
{
	int	st;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	close(fd[1]);
	waitpid(pid, &st, 0);
	init_signal();
	if ((WIFSIGNALED(st) && WTERMSIG(st) == SIGINT)
		|| (WIFEXITED(st) && WEXITSTATUS(st) == 130))
	{
		close(fd[0]);
		sh->heredoc_fd = -1;
		sh->exit_status = 130;
		return (1);
	}
	sh->heredoc_fd = fd[0];
	return (0);
}

int	redir_heredoc(t_shell *sh, t_redir *redir)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		return (print_error("minishell: pipe failed", sh, 1), exit_shell(1), 1);
	pid = fork();
	if (pid == -1)
		return (close(fd[0]), close(fd[1]), exit_shell(1), 1);
	if (pid == 0)
	{
		close(fd[0]);
		heredoc_child(redir, fd[1]);
	}
	return (heredoc_parent_wait(sh, fd, pid));
}

