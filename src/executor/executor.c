/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 23:21:21 by mugenan           #+#    #+#             */
/*   Updated: 2025/08/03 21:26:26 by iguney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	executor(t_cmd *cmds)
{
	int		fd[2];
	int		in_fd;
	pid_t	pid;

	in_fd = 0;
	while (cmds)
	{
		if (cmds->next && pipe(fd) == -1)
			return (perror("pipe"), 1);
		pid = fork();
		if (pid == -1)
			return (perror("fork"), 1);
		if (pid == 0)
			child_process(cmds, in_fd, fd);
		if (in_fd != 0)
			close(in_fd);
		if (cmds->next)
		{
			close(fd[1]);
			in_fd = fd[0];
		}
		waitpid(pid, NULL, 0);
		cmds = cmds->next;
	}
	return (0);
}

void	child_process(t_cmd *cmd, int in_fd, int fd[2])
{
	if (in_fd != 0)
		dup2(in_fd, STDIN_FILENO);
	if (cmd->next)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
	}
	close(fd[1]);
	//handle_redirections(cmd->redir);
	if (!cmd->argv || !cmd->argv[0])
		exit(0);
	if (is_builtin(cmd))
		exec_builtin(cmd);
	// exec_command(cmd); 
}

int	is_builtin(t_cmd *cmd)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (0);
	if (ft_strncmp(cmd->argv[0], "cd", 2))
		return (1);
	if (ft_strncmp(cmd->argv[0], "echo", 4))
		return (1);
	if (ft_strncmp(cmd->argv[0], "pwd", 3))
		return (1);
	if (ft_strncmp(cmd->argv[0], "export", 6))
		return (1);
	if (ft_strncmp(cmd->argv[0], "unset", 5))
		return (1);
	if (ft_strncmp(cmd->argv[0], "env", 3))
		return (1);
	if (ft_strncmp(cmd->argv[0], "exit", 4))
		return (1);
	return (0);
}

int	exec_builtin(t_cmd *cmd)
{
	// if (ft_strcmp(cmd->argv[0], "cd"))
	// 	return (builtin_cd(cmd));
	if (ft_strncmp(cmd->argv[0], "echo", 4))
		return (builtin_echo(cmd->argv));
	// if (ft_strcmp(cmd->argv[0], "pwd"))
	// 	return (builtin_pwd(cmd));
	// if (ft_strcmp(cmd->argv[0], "export"))
	// 	return (builtin_export(cmd));
	// if (ft_strcmp(cmd->argv[0], "unset"))
	// 	return (builtin_unset(cmd));
	// if (ft_strcmp(cmd->argv[0], "env"))
	// 	return (builtin_env(cmd));
	// if (ft_strcmp(cmd->argv[0], "exit"))
	// 	return (builtin_exit(cmd));
	return (1);
}
