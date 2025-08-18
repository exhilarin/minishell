/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 18:36:30 by mugenan           #+#    #+#             */
/*   Updated: 2025/08/18 19:02:01 by mugenan          ###   ########.fr       */
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

int	builtin_cd(t_shell *shell, t_cmd *cmd)
{
	char	*path;
	char	*oldpwd;
	char	cwd[PATH_MAX];

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (perror("getcwd"), 1);
	path = cmd->argv[1];
	if (!path)
		path = get_env_value(shell->env, "HOME");
	if (!path || chdir(path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		if (path)
			ft_putendl_fd(path, 2);
		else
			ft_putendl_fd("HOME not set", 2);
		free(oldpwd);
		return (1);
	}
	set_env_value(&shell->env, "OLDPWD", oldpwd);
	if (getcwd(cwd, sizeof(cwd)))
		set_env_value(&shell->env, "PWD", cwd);
	free(oldpwd);
	return (0);
}
