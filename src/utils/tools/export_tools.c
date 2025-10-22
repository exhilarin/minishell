/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 23:24:31 by mugenan           #+#    #+#             */
/*   Updated: 2025/08/27 23:26:55 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_existing_env(t_env *curr, char *key, char *value)
{
	if (curr->value)
		free(curr->value);
	if (value)
		curr->value = ft_strdup(value);
	else
		curr->value = NULL;
	if (curr->env_line)
		free(curr->env_line);
	if (value)
		curr->env_line = join_key_value(key, value);
	else
		curr->env_line = NULL;
}

t_env	*create_new_env_node(char *key, char *value)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	if (value)
		new_node->value = ft_strdup(value);
	else
		new_node->value = NULL;
	if (value)
		new_node->env_line = join_key_value(key, value);
	else
		new_node->env_line = NULL;
	new_node->next = NULL;
	return (new_node);
}

void	add_to_env_list(t_env **env, t_env *new_node)
{
	t_env	*curr;

	if (!*env)
		*env = new_node;
	else
	{
		curr = *env;
		while (curr->next)
			curr = curr->next;
		curr->next = new_node;
	}
}

t_env	*ms_export_get(t_env *env, char *key)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	ms_export_set(t_env **env, char *key, char *value)
{
	t_env	*curr;
	t_env	*new_node;

	curr = ms_export_get(*env, key);
	if (curr)
	{
		update_existing_env(curr, key, value);
		return ;
	}
	new_node = create_new_env_node(key, value);
	if (!new_node)
		return ;
	add_to_env_list(env, new_node);
}
