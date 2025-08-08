/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 22:42:30 by mugenan           #+#    #+#             */
/*   Updated: 2025/08/08 21:14:10 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*new_env_node(char *env_str)
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

void	init_env(t_shell *shell, char **envp)
{
	t_env	*new;
	t_env	*last;
	int		i;

	shell->env = NULL;
	i = 0;
	while (envp[i])
	{
		new = new_env_node(envp[i]);
		if (!new)
			return ;
		if (!shell->env)
			shell->env = new;
		else
		{
			last = shell->env;
			while (last->next)
				last = last->next;
			last->next = new;
		}
		i++;
	}
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
