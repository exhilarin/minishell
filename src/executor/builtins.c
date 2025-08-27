/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 04:36:45 by mugenan           #+#    #+#             */
/*   Updated: 2025/08/26 18:01:28 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_cmd *cmd)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (0);
	if (!ft_strcmp(cmd->argv[0], "cd"))
		return (1);
	if (!ft_strcmp(cmd->argv[0], "echo"))
		return (1);
	if (!ft_strcmp(cmd->argv[0], "pwd"))
		return (1);
	if (!ft_strcmp(cmd->argv[0], "export"))
		return (1);
	if (!ft_strcmp(cmd->argv[0], "unset"))
		return (1);
	if (!ft_strcmp(cmd->argv[0], "env"))
		return (1);
	if (!ft_strcmp(cmd->argv[0], "exit"))
		return (1);
	return (0);
}

void	exec_builtin(t_shell *shell, t_cmd *cmd)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return ;
	if (!ft_strcmp(cmd->argv[0], "echo"))
		builtin_echo(cmd->argv);
	else if (!ft_strcmp(cmd->argv[0], "export"))
		builtin_export(shell, cmd);
	else if (!ft_strcmp(cmd->argv[0], "env"))
		builtin_env(shell->env);
	else if (!ft_strcmp(cmd->argv[0], "exit"))
		builtin_exit(cmd->argv);
	else if (!ft_strcmp(cmd->argv[0], "unset"))
		builtin_unset(&shell->env, cmd);
	else if (!ft_strcmp(cmd->argv[0], "cd"))
		builtin_cd(shell, cmd);
	else if (!ft_strcmp(cmd->argv[0], "pwd"))
		builtin_pwd();
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
