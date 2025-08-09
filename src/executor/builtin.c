/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxc <fxc@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 04:36:45 by mugenan           #+#    #+#             */
/*   Updated: 2025/08/09 23:32:15 by fxc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_shell *shell)
{
	// if (ft_strcmp(cmd->argv[0], "cd"))
	// 	return (builtin_cd(cmd));
	if (ft_strncmp(shell->command_list->argv[0], "echo", 4))
		return (builtin_echo(shell->command_list->argv));
	// if (ft_strncmp(cmd->argv[0], "pwd", 3))
	// 	return (builtin_pwd(cmd));
	if (ft_strncmp(shell->command_list->argv[0], "export", 6))
		return (builtin_export(shell->env));
	// if (ft_strncmp(cmd->argv[0], "unset", 5))
	// 	return (builtin_unset(cmd));
	if (ft_strncmp(shell->command_list->argv[0], "env", 3))
		return (builtin_env(shell->env));
	if (ft_strncmp(shell->command_list->argv[0], "exit", 4))
		return (builtin_exit(shell->command_list->argv, shell));
	return (1);
}

int	is_builtin(t_cmd *cmd)
{
	if (!cmd || !cmd->argv
		|| !cmd->argv[0])
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

int	builtin_needs_parent(char *name)
{
	return (ft_strncmp(name, "cd", 2)
		|| ft_strncmp(name, "export", 6)
		|| ft_strncmp(name, "unset", 5)
		|| ft_strncmp(name, "exit", 4));
}
