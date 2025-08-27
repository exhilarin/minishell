/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 23:21:21 by mugenan           #+#    #+#             */
/*   Updated: 2025/08/27 01:32:25 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	exec_command(t_shell *shell, t_cmd *cmd)
{
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
	   char **envp = env_list_to_array(shell->env);
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

static	void	child_process(t_shell *shell, t_cmd *cmd, int fd[2])
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
		child_process(shell, cmd, fd);
	parent_process(shell, cmd, fd);
}

void	executor(t_shell *shell, t_cmd *cmd)
{
	int		fd[2];
	pid_t	pids[1024];
	int		count;
	int		status;
	int		i;

	count = 0;
	status = 0;
	g_signal_code = 1;
	ft_memset(pids, 0, sizeof(pids));
	if (check_special_case(shell, cmd, cmd->redir))
		return ;
	while (cmd)
	{
		run_command_process(shell, cmd, fd, &pids[count]);
		if (shell->heredoc_fd != -1)
			close(shell->heredoc_fd);
		shell->heredoc_fd = -1;
		count++;
		cmd = cmd->next;
	}
	i = 0;
	while (i < count)
	{
		waitpid(pids[i], &status, 0);
		i++;
	}
	if (WIFEXITED(status))
		exit_status_manager(WEXITSTATUS(status), 1);
	else if (WIFSIGNALED(status))
		exit_status_manager(128 + WTERMSIG(status), 1);
}
