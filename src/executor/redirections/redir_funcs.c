/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 18:10:34 by mugenan           #+#    #+#             */
/*   Updated: 2025/08/27 21:34:56 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redir_in(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(redir->file, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		exit_shell(1, NULL);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
		exit_shell(1, "minishell: dup2 failed\n");
	close(fd);
}

static void	redir_out(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(redir->file, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		exit_shell(1, NULL);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
		exit_shell(1, "minishell: dup2 failed\n");
	close(fd);
}

static void	redir_append(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(redir->file, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		exit_shell(1, NULL);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
		exit_shell(1, "minishell: dup2 failed\n");
	close(fd);
}

void	handle_redirections(t_shell *shell, t_redir *redir, int process)
{
	while (redir)
	{
		if (redir->type == REDIR_IN)
			redir_in(redir);
		else if (redir->type == REDIR_OUT)
			redir_out(redir);
		else if (redir->type == APPEND)
			redir_append(redir);
		else if (redir->type == HEREDOC && process == 1)
			redir_heredoc(shell, redir);
		redir = redir->next;
	}
}
