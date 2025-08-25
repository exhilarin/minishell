/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 23:21:21 by mugenan           #+#    #+#             */
/*   Updated: 2025/08/26 02:38:55 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	executor(t_shell *shell, t_cmd *cmd)
{
	int		fd[2];
	pid_t	pid;

	if (check_special_case(shell, cmd, cmd->redir))
		return ;
	while (cmd)
	{
		if (handle_heredoc(shell, cmd->redir))
			return ;
		if (cmd->next && pipe(fd) == -1)
			exit_shell(1, "minishell: pipe failed\n");
		pid = fork();
		if (pid == -1)
			exit_shell(1, "minishell: fork failed\n");
		if (pid == 0)
			child_process(shell, cmd, fd);
		parent_process(shell, cmd, fd, pid);
		if (shell->heredoc_fd != -1)
			close(shell->heredoc_fd);
		shell->heredoc_fd = -1;
		cmd = cmd->next;
	}
}

void	child_process(t_shell *shell, t_cmd *cmd, int fd[2])
{
	if (shell->in_fd != -1)
	{
		if (dup2(shell->in_fd, STDIN_FILENO) == -1)
			exit_shell(1, "minishell: dup2 failed\n");
		close(shell->in_fd);
	}
	else if (shell->heredoc_fd != -1)
	{
		if (dup2(shell->heredoc_fd, STDIN_FILENO) == -1)
			exit_shell(1, "minishell: dup2 failed\n");
		close(shell->heredoc_fd);
	}
	if (cmd->next)
	{
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			exit_shell(1, "minishell: dup2 failed\n");
		close(fd[1]);
	}
	if (cmd->redir)
		handle_redirections(shell, cmd->redir, 0);
	if (!cmd->argv || !cmd->argv[0])
		exit_shell(0, NULL);
	exec_command(shell, cmd);
}

void	parent_process(t_shell *shell, t_cmd *cmd, int fd[2], pid_t pid)
{
	if (shell->in_fd != -1)
		close(shell->in_fd);
	if (cmd->next)
	{
		close(fd[1]);
		shell->in_fd = fd[0];
	}
	else if (shell->in_fd != -1)
	{
		close(fd[0]);
		shell->in_fd = -1;
	}
	waitpid(pid, NULL, 0);
}

static void	exec_error(t_shell *shell, t_cmd *cmd)
{
	if (shell->exec->flag == 1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd->argv[0], STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		exit_shell(1, NULL);
	}
	else if (!shell->exec->cmd_path)
		exit_shell(127, "minishell: command not found\n");
	else if (access(shell->exec->cmd_path, X_OK) != 0)
	{
		ft_putstr_fd("minishell: permission denied: ", STDERR_FILENO);
		ft_putendl_fd(cmd->argv[0], STDERR_FILENO);
		exit_shell(126, NULL);
	}
}

void	exec_command(t_shell *shell, t_cmd *cmd)
{
	if (is_builtin(cmd))
	{
		exec_builtin(shell, cmd);
		exit_shell(shell->exit_status, NULL);
	}
	shell->exec = init_exec();
	if (!shell->exec || !cmd->argv[0])
		exit_shell(1, NULL);
	shell->exec->cmd_path = get_cmd_path(shell, cmd);
	exec_error(shell, cmd);
	if (execve(shell->exec->cmd_path, cmd->argv,
			env_list_to_array(shell->env)) == -1)
	{
		ft_putstr_fd("minishell: execution failed: ", STDERR_FILENO);
		ft_putendl_fd(cmd->argv[0], STDERR_FILENO);
		exit_shell(126, NULL);
	}
}
