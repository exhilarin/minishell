/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 23:21:21 by mugenan           #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2025/08/04 07:17:18 by mugenan          ###   ########.fr       */
=======
/*   Updated: 2025/08/08 21:27:36 by mugenan          ###   ########.fr       */
>>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

<<<<<<< Updated upstream
int	executor(t_cmd *cmds)
=======
t_exec *init_exec(void)
{
    t_exec *exec;

    exec = malloc(sizeof(t_exec));
    if (!exec)
        return (NULL);
    exec->cmd_path = NULL;
    exec->paths = NULL;
    exec->envp = NULL;
    return (exec);
}

int	executor(t_shell *shell)
>>>>>>> Stashed changes
{
	int		fd[2];
	int		in_fd;
	pid_t	pid;

<<<<<<< Updated upstream
	in_fd = 0;
	if (cmds && !cmds->next && is_builtin(cmds)
		&& builtin_needs_parent(cmds->argv[0]))
		return (exec_builtin_parent(cmds));
	while (cmds)
=======
	in_fd = -1;
	shell->exec = init_exec();
	if (shell->command_list && !shell->command_list->next
		&& builtin_needs_parent(shell->command_list->argv[0]))
		return (exec_builtin(shell));
	while (shell->command_list)
>>>>>>> Stashed changes
	{
		is_redir_heredoc(cmds->redir, cmds);
		if (cmds->next && pipe(fd) == -1)
			return (perror("pipe"), 1);
		pid = fork();
		if (pid == -1)
			return (perror("fork"), 1);
		if (pid == 0)
			child_process(cmds, in_fd, fd);
		parent_process(cmds, &in_fd, fd, pid);
		cmds = cmds->next;
	}
	return (0);
}

void	child_process(t_cmd *cmd, int in_fd, int fd[2])
{
	if (in_fd != -1)
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

void	parent_process(t_cmd *cmds, int in_fd, int *fd, pid_t pid)
{
<<<<<<< Updated upstream
	if (in_fd != 0)
		close(in_fd);
=======
	if (*in_fd != -1)
		close(*in_fd);
>>>>>>> Stashed changes
	if (cmds->next)
	{
		close(fd[1]);
		in_fd = fd[0];
	}
	waitpid(pid, NULL, 0);
}
<<<<<<< Updated upstream
=======

void	exec_command(t_shell *shell)
{
	char *cmd_path;
	
	shell->exec = NULL;
	if (!shell->command_list->argv[0])
		exit(shutdown_shell(shell));
	cmd_path = get_cmd_path(shell);
	if (!cmd_path)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(shell->command_list->argv[0], 2);
		exit(127);
	}
	if (execve(cmd_path,
			shell->command_list->argv, env_list_to_array(shell->env)) == -1)
	{
		perror("minishell: execve");
		exit(126);
	}
}

char	*get_cmd_path(t_shell *shell)
{
	char	*tmp;
	char	*full;
	char	*cmd;
	char 	**path;
	int		i;
	
	
	cmd = shell->command_list->argv[0];
	if (ft_strchr(cmd, '/') && access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	path = ft_split(get_env_value(shell->env, "PATH"), ':'); //leak condition!
	if (!path)
		return (NULL);
	i = -1;
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], "/");
		full = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full, X_OK) == 0)
			return (full);
		free(full);
	}
	return (NULL);
}
>>>>>>> Stashed changes
