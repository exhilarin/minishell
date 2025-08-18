/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 22:42:30 by mugenan           #+#    #+#             */
/*   Updated: 2025/08/18 09:10:07 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_env_node(char *env_str)
{
	t_env	*node;
	int		i;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->env_line = ft_strdup(env_str);
	if (!node->env_line)
		return (free(node), NULL);
	i = 0;
	while (env_str[i] && env_str[i] != '=')
		i++;
	node->key = ft_substr(env_str, 0, i);
	if (!node->key)
		return (free(node->env_line), free(node), NULL);
	if (env_str[i] == '=')
		node->value = ft_strdup(env_str + i + 1);
	else
		node->value = ft_strdup("");
	if (!node->value)
		return (free(node->key), free(node->env_line), free(node), NULL);
	node->next = NULL;
	return (node);
}

char	**env_list_to_array(t_env *env)
{
	char	**envp;
	int		i;
	t_env	*curr;

	i = 0;
	curr = env;
	while (curr)
	{
		i++;
		curr = curr->next;
	}
	envp = malloc(sizeof(char *) * (i + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		envp[i] = ft_strdup(env->env_line);
		if (!envp[i])
			return (NULL);
		env = env->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

char	*get_env_value(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		if (env->env_line)
			free(env->env_line);
		if (env->key)
			free(env->key);
		if (env->value)
			free(env->value);
		free(env);
		env = tmp;
	}
}
