/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 18:36:30 by mugenan           #+#    #+#             */
/*   Updated: 2025/08/26 17:52:31 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	change_directory(t_shell *shell, char *path, char *oldpwd)
{
	char	cwd[PATH_MAX];

	if (!path || chdir(path) == -1)
	{
		if (path)
		{
			ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
			ft_putendl_fd(path, STDERR_FILENO);
			exit_status_manager(1, 1);
		}
		return (0);
	}
	set_env_value(&shell->env, "OLDPWD", oldpwd);
	if (getcwd(cwd, sizeof(cwd)))
		set_env_value(&shell->env, "PWD", cwd);
	exit_status_manager(0, 1);
	return (1);
}

void	builtin_cd(t_shell *shell, t_cmd *cmd)
{
	char	*oldpwd;
	char	*path;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		ft_putendl_fd("minishell: cd: getcwd failed", STDERR_FILENO);
		exit_status_manager(1, 1);
		return ;
	}
	path = cmd->argv[1];
	if (!path)
		path = get_env_value(shell->env, "HOME");
	if (!change_directory(shell, path, oldpwd))
	{
		free(oldpwd);
		return ;
	}
	free(oldpwd);
}
