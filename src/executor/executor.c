/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 23:21:21 by mugenan           #+#    #+#             */
/*   Updated: 2025/08/27 21:04:20 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	child_process(t_shell *shell, t_cmd *cmd, int fd[2])
{
	if (shell->heredoc_fd != -1)
	{
		if (dup2(shell->heredoc_fd, STDIN_FILENO) == -1)
			exit_shell(1, "minishell: dup2 failed\n");
		close(shell->heredoc_fd);
	}
	else if (shell->in_fd != -1)
	{
		if (dup2(shell->in_fd, STDIN_FILENO) == -1)
			exit_shell(1, "minishell: dup2 failed\n");
		close(shell->in_fd);
	}
	if (cmd->next)
	{
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			exit_shell(1, "minishell: dup2 failed\n");
		close(fd[1]);
	}
}

static	void	parent_process(t_shell *shell, t_cmd *cmd, int fd[2])
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
}

static void	exec_command(t_shell *shell, t_cmd *cmd)
{
	char	**envp;

	if (is_builtin(cmd))
	{
		exec_builtin(shell, cmd);
		exit_shell(exit_status_manager(0, 0), NULL);
	}
	shell->exec = init_exec();
	if (!shell->exec || !cmd->argv[0])
		exit_shell(1, NULL);
	shell->exec->cmd_path = get_cmd_path(shell, cmd);
	exec_error(shell, cmd);
	envp = env_list_to_array(shell->env);
	if (execve(shell->exec->cmd_path, cmd->argv, envp) == -1)
	{
		ft_putstr_fd("minishell: execution failed: ", STDERR_FILENO);
		ft_putendl_fd(cmd->argv[0], STDERR_FILENO);
		perror("execve");
		free_envp(envp);
		exit_shell(126, NULL);
	}
	free_envp(envp);
}

static void	run_command_process(t_shell *shell, t_cmd *cmd, int fd[2],
		pid_t *pid)
{
	if (handle_heredoc(shell, cmd->redir))
		return ;
	if (cmd->next && pipe(fd) == -1)
		exit_shell(1, "minishell: pipe failed\n");
	*pid = fork();
	if (*pid == -1)
		exit_shell(1, "minishell: fork failed\n");
	if (*pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		child_process(shell, cmd, fd);
		if (cmd->redir)
			handle_redirections(shell, cmd->redir, 0);
		if (!cmd->argv || !cmd->argv[0])
			exit_shell(0, NULL);
		exec_command(shell, cmd);
	}
	parent_process(shell, cmd, fd);
}

void	executor(t_shell *shell, t_cmd *cmd)
{
	int		fd[2];
	pid_t	pids[1024];
	int		count;

	count = 0;
	g_signal_code = 1;
	discard_signals();
	ft_memset(pids, 0, sizeof(pid_t) * 1024);
	if (check_special_case(shell, cmd, cmd->redir))
	{
		init_signal();
		g_signal_code = 0;
		return ;
	}
	while (cmd)
	{
		run_command_process(shell, cmd, fd, &pids[count]);
		count++;
		cmd = cmd->next;
	}
	wait_and_set_status(pids, count);
	init_signal();
	g_signal_code = 0;
}
