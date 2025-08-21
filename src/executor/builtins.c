/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 04:36:45 by mugenan           #+#    #+#             */
/*   Updated: 2025/08/22 01:59:11 by ilyas-guney      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_cmd *cmd)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (0);
	if (ft_strlen(cmd->argv[0]) == 2 && ft_strncmp(cmd->argv[0], "cd", 2))
		return (1);
	if (ft_strlen(cmd->argv[0]) == 4 && ft_strncmp(cmd->argv[0], "echo", 4))
		return (1);
	if (ft_strlen(cmd->argv[0]) == 3 && ft_strncmp(cmd->argv[0], "pwd", 3))
		return (1);
	if (ft_strlen(cmd->argv[0]) == 6 && ft_strncmp(cmd->argv[0], "export", 6))
		return (1);
	if (ft_strlen(cmd->argv[0]) == 5 && ft_strncmp(cmd->argv[0], "unset", 5))
		return (1);
	if (ft_strlen(cmd->argv[0]) == 3 && ft_strncmp(cmd->argv[0], "env", 3))
		return (1);
	if (ft_strlen(cmd->argv[0]) == 4 && ft_strncmp(cmd->argv[0], "exit", 4))
		return (1);
	return (0);
}

int	exec_builtin(t_shell *shell, t_cmd *cmd)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (1);

	if (ft_strncmp(cmd->argv[0], "echo", 4))
		return (builtin_echo(cmd->argv));
	if (ft_strncmp(cmd->argv[0], "export", 6))
		return (builtin_export(&shell->env, cmd));
	if (ft_strncmp(cmd->argv[0], "env", 3))
		return (builtin_env(shell->env));
	if (ft_strncmp(cmd->argv[0], "exit", 4))
		return (builtin_exit(cmd->argv, shell));
	if (ft_strncmp(cmd->argv[0], "unset", 5))
		return (builtin_unset(&shell->env, cmd));
	if (ft_strncmp(cmd->argv[0], "cd", 2))
		return (builtin_cd(shell, cmd));
	if (ft_strncmp(cmd->argv[0], "pwd", 3))
		return (builtin_pwd());
	return (1);
}

static void	free_char_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_exec(t_exec *exec)
{
	if (!exec)
		return ;
	if (exec->cmd_path)
	{
		free(exec->cmd_path);
		exec->cmd_path = NULL;
	}
	if (exec->paths)
	{
		free_char_array(exec->paths);
		exec->paths = NULL;
	}
	if (exec->envp)
	{
		free_char_array(exec->envp);
		exec->envp = NULL;
	}
	free(exec);
}
