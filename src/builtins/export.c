/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 06:39:26 by mugenan           #+#    #+#             */
/*   Updated: 2025/08/18 09:12:15 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_export(t_env **env, t_cmd *cmd)
{
	t_env	*current;
	t_env	*node;
	int		i;

	if (!cmd->argv[1])
		return (builtin_print_export(*env));
	i = 1;
	while (cmd->argv[i])
	{
		node = new_env_node(cmd->argv[i]);
		if (!node)
			return (1);
		if (!*env)
			*env = node;
		else
		{
			current = *env;
			while (current->next)
				current = current->next;
			current->next = node;
		}
		i++;
	}
	return (0);
}

static t_env	*find_min_env(t_env *env, t_env *last_min)
{
	t_env	*min;
	t_env	*curr;

	min = NULL;
	curr = env;
	while (curr)
	{
		if ((!last_min || ft_strcmp(curr->key, last_min->key) > 0)
			&& (!min || ft_strcmp(curr->key, min->key) < 0))
			min = curr;
		curr = curr->next;
	}
	return (min);
}

int	builtin_print_export(t_env *env)
{
	t_env	*last_min;
	t_env	*min;

	last_min = NULL;
	while (1)
	{
		min = find_min_env(env, last_min);
		if (!min)
			break ;
		printf("declare -x %s", min->key);
		if (min->value && min->value[0])
			printf("=\"%s\"", min->value);
		printf("\n");
		last_min = min;
	}
	return (0);
}
