/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 23:21:21 by mugenan           #+#    #+#             */
/*   Updated: 2025/08/22 01:56:12 by ilyas-guney      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	executor(t_shell *shell, t_cmd *cmd)
{
	int		return_value;
	int		fd[2];
	pid_t	pid;

	return_value = check_special_case(shell, cmd, cmd->redir);
	if (return_value != -1)
		return (return_value);
	while (cmd)
	{
		handle_heredoc(shell, cmd->redir);
		if (cmd->next && pipe(fd) == -1)
			return (perror("minishell: pipe"), 1);
		pid = fork();
		if (pid == -1)
			return (perror("minishell: fork"), 1);
		if (pid == 0)
			child_process(shell, cmd, fd);
		parent_process(shell, cmd, fd, pid);
		if (shell->heredoc_fd != -1)
			close(shell->heredoc_fd);
		shell->heredoc_fd = -1;
		cmd = cmd->next;
	}
	return (0);
}

void	child_process(t_shell *shell, t_cmd *cmd, int fd[2])
{
	if (shell->in_fd != -1)
	{
		dup2(shell->in_fd, STDIN_FILENO);
		close(shell->in_fd);
	}
	else if (shell->heredoc_fd != -1)
	{
		dup2(shell->heredoc_fd, STDIN_FILENO);
		close(shell->heredoc_fd);
	}
	if (cmd->next)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	if (cmd->redir)
		handle_redirections(shell, cmd->redir, 0);
	if (!cmd->argv || !cmd->argv[0])
	{
		shell->exit_status = 0;
		exit(shutdown_shell(shell));
	}
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

void	exec_command(t_shell *shell, t_cmd *cmd)
{
	if (is_builtin(cmd))
	{
		shell->exit_status = exec_builtin(shell, cmd);
		exit(shutdown_shell(shell));
	}
	shell->exec = init_exec();
	if (!shell->exec)
		exit(shutdown_shell(shell));
	if (!cmd->argv[0])
		exit(shutdown_shell(shell));
	shell->exec->cmd_path = get_cmd_path(shell, cmd);
	if (!shell->exec->cmd_path)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(cmd->argv[0], 2);
		shell->exit_status = 127;
		exit(shutdown_shell(shell));
	}
	if (execve(shell->exec->cmd_path, cmd->argv, env_list_to_array(shell->env)) == -1)
	{
		perror("minishell: execve");
		shell->exit_status = 126;
		exit(shutdown_shell(shell));
	}
}
