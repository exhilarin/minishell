/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 22:42:30 by mugenan           #+#    #+#             */
/*   Updated: 2025/08/27 22:11:02 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*validate_env_allocs(t_env *node, char *env_str, int eq_pos)
{
	if (env_str[eq_pos] == '=' && !node->value)
		return (free(node->key), free(node), NULL);
	if (env_str[eq_pos] == '=' && !node->env_line)
		return (free(node->key), free(node->value), free(node), NULL);
	return (node);
}

t_env	*new_env_node(char *env_str)
{
	t_env	*node;
	int		i;

	node = init_env_node();
	if (!node)
		return (NULL);
	i = 0;
	while (env_str[i] && env_str[i] != '=')
		i++;
	node->key = ft_substr(env_str, 0, i);
	if (!node->key)
		return (free(node), NULL);
	if (env_str[i] == '=')
	{
		node->value = ft_strdup(env_str + i + 1);
		node->env_line = ft_strdup(env_str);
	}
	else
	{
		node->value = NULL;
		node->env_line = NULL;
	}
	return (validate_env_allocs(node, env_str, i));
}

static char	**fill_envp_array(t_env *env, char **envp)
{
	int	i;

	i = 0;
	while (env)
	{
		if (env->value != NULL)
		{
			envp[i] = join_key_value(env->key, env->value);
			if (!envp[i])
			{
				while (i-- > 0)
					free(envp[i]);
				free(envp);
				return (NULL);
			}
			i++;
		}
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

char	**env_list_to_array(t_env *env)
{
	char	**envp;
	int		count;
	t_env	*curr;

	count = 0;
	curr = env;
	while (curr)
	{
		if (curr->value != NULL)
			count++;
		curr = curr->next;
	}
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	return (fill_envp_array(env, envp));
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
