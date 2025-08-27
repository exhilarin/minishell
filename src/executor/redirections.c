/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 18:10:34 by mugenan           #+#    #+#             */
/*   Updated: 2025/08/26 18:11:19 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtin_with_redir(t_shell *shell, t_cmd *cmd)
{
	int		stdin_backup;
	int		stdout_backup;
	t_redir	*redir;
	int		error;

	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	if (stdin_backup == -1 || stdout_backup == -1)
	{
		if (stdin_backup != -1)
			close(stdin_backup);
		if (stdout_backup != -1)
			close(stdout_backup);
		exit_status_manager(1, 1);
		return ;
	}
	error = 0;
	redir = cmd->redir;
	while (redir && !error)
	{
		if (redir->type == REDIR_IN)
		{
			int fd = open(redir->file, O_RDONLY);
			if (fd == -1)
			{
				ft_putstr_fd("minishell: ", STDERR_FILENO);
				ft_putstr_fd(redir->file, STDERR_FILENO);
				ft_putstr_fd(": ", STDERR_FILENO);
				ft_putendl_fd(strerror(errno), STDERR_FILENO);
				error = 1;
			}
			else
			{
				if (dup2(fd, STDIN_FILENO) == -1)
					error = 1;
				close(fd);
			}
		}
		else if (redir->type == REDIR_OUT)
		{
			int fd = open(redir->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (fd == -1)
			{
				ft_putstr_fd("minishell: ", STDERR_FILENO);
				ft_putstr_fd(redir->file, STDERR_FILENO);
				ft_putstr_fd(": ", STDERR_FILENO);
				ft_putendl_fd(strerror(errno), STDERR_FILENO);
				error = 1;
			}
			else
			{
				if (dup2(fd, STDOUT_FILENO) == -1)
					error = 1;
				close(fd);
			}
		}
		else if (redir->type == APPEND)
		{
			int fd = open(redir->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (fd == -1)
			{
				ft_putstr_fd("minishell: ", STDERR_FILENO);
				ft_putstr_fd(redir->file, STDERR_FILENO);
				ft_putstr_fd(": ", STDERR_FILENO);
				ft_putendl_fd(strerror(errno), STDERR_FILENO);
				error = 1;
			}
			else
			{
				if (dup2(fd, STDOUT_FILENO) == -1)
					error = 1;
				close(fd);
			}
		}
		else if (redir->type == HEREDOC)
		{
			if (redir_heredoc(shell, redir))
				error = 1;
		}
		redir = redir->next;
	}
	if (exit_status_manager(0, 0) == 130 || error)
	{
		if (dup2(stdin_backup, STDIN_FILENO) == -1
			|| dup2(stdout_backup, STDOUT_FILENO) == -1)
		{
			close(stdin_backup);
			close(stdout_backup);
			exit_status_manager(1, 1);
			return ;
		}
		close(stdin_backup);
		close(stdout_backup);
		if (error)
			exit_status_manager(1, 1);
		return ;
	}
	exec_builtin(shell, cmd);
	if (dup2(stdin_backup, STDIN_FILENO) == -1
		|| dup2(stdout_backup, STDOUT_FILENO) == -1)
	{
		close(stdin_backup);
		close(stdout_backup);
		exit_status_manager(1, 1);
		return ;
	}
	close(stdin_backup);
	close(stdout_backup);
}

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
