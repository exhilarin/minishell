/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 20:43:35 by mugenan           #+#    #+#             */
/*   Updated: 2025/08/16 17:50:30 by iguney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin_with_redir(t_shell *shell)
{
	int	stdin_backup;
	int	stdout_backup;
	int	return_value;

	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	if (stdin_backup == -1 || stdout_backup == -1)
	{
		ft_putstr_fd("minishell: exit: dup failed\n", STDERR_FILENO);
		shell->exit_status = 1;
		exit(shutdown_shell(shell));
	}
	if (shell->command_list->redir)
		handle_redirections(shell, shell->command_list->redir);
	return_value = exec_builtin(shell);
	if (dup2(stdin_backup, STDIN_FILENO) == -1
		|| dup2(stdout_backup, STDOUT_FILENO) == -1)
	{
		ft_putstr_fd("minishell: exit: dup2 failed\n", STDERR_FILENO);
		shell->exit_status = 1;
		exit(shutdown_shell(shell));
	}
	close(stdin_backup);
	close(stdout_backup);
	return (return_value);
}

static void	redir_in(t_shell *shell, t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(redir->file, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		shell->exit_status = 1;
		exit(shutdown_shell(shell));
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		ft_putstr_fd("minishell: dup2 failed\n", STDERR_FILENO);
		shell->exit_status = 1;
		exit(shutdown_shell(shell));
	}
	close(fd);
}

static void	redir_out(t_shell *shell, t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(redir->file, STDERR_FILENO);
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
		shell->exit_status = 1;
		exit(shutdown_shell(shell));
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		ft_putstr_fd("minishell: dup2 failed\n", STDERR_FILENO);
		shell->exit_status = 1;
		exit(shutdown_shell(shell));
	}
	close(fd);
}

static void	redir_append(t_shell *shell, t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(redir->file, STDERR_FILENO);
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
		shell->exit_status = 1;
		exit(shutdown_shell(shell));
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		ft_putstr_fd("minishell: dup2 failed\n", STDERR_FILENO);
		shell->exit_status = 1;
		exit(shutdown_shell(shell));
	}
	close(fd);
}

void	handle_redirections(t_shell *shell, t_redir *redir)
{
	while (redir)
	{
		if (redir->type == REDIR_IN)
			redir_in(shell, redir);
		else if (redir->type == REDIR_OUT)
			redir_out(shell, redir);
		else if (redir->type == APPEND)
			redir_append(shell, redir);
		else if (redir->type == HEREDOC)
			redir_heredoc(shell, redir, 0);
		redir = redir->next;
	}
}
