/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 23:21:21 by mugenan           #+#    #+#             */
/*   Updated: 2025/08/15 04:59:28 by iguney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	executor(t_shell *shell)
{
	int		in_fd;
	int		fd[2];
	pid_t	pid;

	in_fd = -1;
	if (!shell->command_list->argv)
		return (free_all(shell));
	if (shell->command_list && !shell->command_list->next
		&& builtins_on_parent(shell->command_list->argv[0]))
		return (exec_builtin_with_redir(shell));
	while (shell->command_list)
	{
		if (shell->command_list->next && pipe(fd) == -1)
			return (perror("pipe"), 1);
		pid = fork();
		if (pid == -1)
			return (perror("fork"), 1);
		if (pid == 0)
			child_process(shell, in_fd, fd);
		parent_process(shell->command_list, &in_fd, fd, pid);
		shell->command_list = shell->command_list->next;
	}
	return (0);
}

void	child_process(t_shell *shell, int in_fd, int fd[2])
{
	if (in_fd != -1)
		dup2(in_fd, STDIN_FILENO);
	if (shell->command_list->next)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	if (shell->command_list->redir)
		handle_redirections(shell, shell->command_list->redir);
	if (!shell->command_list->argv || !shell->command_list->argv[0])
	{
		shell->exit_status = 0;
		exit(shutdown_shell(shell));
	}
	if (is_builtin(shell->command_list))
		exit(exec_builtin(shell));
	exec_command(shell);
}

void	parent_process(t_cmd *cmds, int *in_fd, int *fd, pid_t pid)
{
	if (*in_fd != -1)
		close(*in_fd);
	if (cmds->next)
	{
		close(fd[1]);
		*in_fd = fd[0];
	}
	waitpid (pid, NULL, 0);
}

void	exec_command(t_shell *shell)
{
	shell->exec = init_exec();
	if (!shell->command_list->argv[0])
		exit(shutdown_shell(shell));
	shell->exec->cmd_path = get_cmd_path(shell);
	if (!shell->exec->cmd_path)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(shell->command_list->argv[0], 2);
		shell->exit_status = 127;
		exit(shutdown_shell(shell));
	}
	if (execve(shell->exec->cmd_path,
			shell->command_list->argv, env_list_to_array(shell->env)) == -1)
	{
		perror("minishell: execve");
		shell->exit_status = 126;
		exit(shutdown_shell(shell));
	}
}

char	*get_cmd_path(t_shell *shell)
{
	char	*tmp;
	char	*full;
	char	*cmd;
	int		i;

	cmd = shell->command_list->argv[0];
	if (ft_strchr(cmd, '/') && access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	shell->exec->paths = ft_split(get_env_value(shell->env, "PATH"), ':');
	if (!shell->exec->paths)
		return (NULL);
	i = -1;
	while (shell->exec->paths[++i])
	{
		tmp = ft_strjoin(shell->exec->paths[i], "/");
		full = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full, X_OK) == 0)
			return (full);
		free(full);
	}
	return (NULL);
}
