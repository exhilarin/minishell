/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 18:36:30 by mugenan           #+#    #+#             */
/*   Updated: 2025/08/23 01:15:23 by ilyas-guney      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_env_node(t_env **env, char *key, char *value)
{
	t_env	*tmp;
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	if (!*env)
	{
		*env = new;
		return ;
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

static void	set_env_value(t_env **env, char *key, char *value)
{
	t_env	*tmp;

	if (!key || !value)
		return ;
	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return ;
		}
		tmp = tmp->next;
	}
	add_env_node(env, key, value);
}

static int	change_directory(t_shell *shell, char *path, char *oldpwd)
{
	char	cwd[PATH_MAX];

	if (!path || chdir(path) == -1)
	{
		if (path)
		{
			print_error("minishell: cd: ", shell, 1);
			ft_putendl_fd(path, STDERR_FILENO);
		}
		return (0);
	}
	set_env_value(&shell->env, "OLDPWD", oldpwd);
	if (getcwd(cwd, sizeof(cwd)))
		set_env_value(&shell->env, "PWD", cwd);
	return (1);
}

void	builtin_cd(t_shell *shell, t_cmd *cmd)
{
	char	*oldpwd;
	char	*path;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		print_error("minishell: cd: getcwd failed\n", shell, 1);
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
	shell->exit_status = 0;
}
