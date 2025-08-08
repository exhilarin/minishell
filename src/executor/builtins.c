/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 04:36:45 by mugenan           #+#    #+#             */
<<<<<<< Updated upstream:src/executor/builtins.c
/*   Updated: 2025/08/04 07:19:46 by mugenan          ###   ########.fr       */
=======
/*   Updated: 2025/08/08 19:06:00 by mugenan          ###   ########.fr       */
>>>>>>> Stashed changes:src/executor/builtin.c
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	builtin_needs_parent(char *name)
{
<<<<<<< Updated upstream:src/executor/builtins.c
	return (!ft_strncmp(name, "cd", 2)
		|| !ft_strncmp(name, "export", 6)
		|| !ft_strncmp(name, "unset", 5)
		|| !ft_strncmp(name, "exit", 4));
}
=======
	return (ft_strncmp(name, "cd", 2)
		|| ft_strncmp(name, "export", 6)
		|| ft_strncmp(name, "unset", 5)
		|| ft_strncmp(name, "exit", 4));
}
>>>>>>> Stashed changes:src/executor/builtin.c
