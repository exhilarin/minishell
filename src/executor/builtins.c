/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 04:36:45 by mugenan           #+#    #+#             */
/*   Updated: 2025/08/27 22:38:27 by mugenan          ###   ########.fr       */
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
