/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 18:36:30 by mugenan           #+#    #+#             */
/*   Updated: 2025/08/28 04:04:28 by iguney           ###   ########.fr       */
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
			ft_putstr_fd(path, STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
			ft_putendl_fd(strerror(errno), STDERR_FILENO);
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

static int	count_cd_args(t_cmd *cmd)
{
	int	arg_count;

	arg_count = 0;
	while (cmd->argv[arg_count])
		arg_count++;
	if (arg_count > 2)
	{
		ft_putendl_fd("minishell: cd: too many arguments", STDERR_FILENO);
		exit_status_manager(1, 1);
		return (0);
	}
	return (1);
}

static char	*get_cd_oldpwd(void)
{
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		ft_putendl_fd("minishell: cd: getcwd failed", STDERR_FILENO);
		exit_status_manager(1, 1);
		return (NULL);
	}
	return (oldpwd);
}

static char	*determine_cd_path(t_shell *shell, t_cmd *cmd)
{
	char	*path;

	path = cmd->argv[1];
	if (!path)
		path = get_env_value(shell->env, "HOME");
	return (path);
}

void	builtin_cd(t_shell *shell, t_cmd *cmd)
{
	char	*oldpwd;
	char	*path;

	if (!count_cd_args(cmd))
		return ;
	oldpwd = get_cd_oldpwd();
	if (!oldpwd)
		return ;
	path = determine_cd_path(shell, cmd);
	if (!change_directory(shell, path, oldpwd))
	{
		free(oldpwd);
		return ;
	}
	free(oldpwd);
}
