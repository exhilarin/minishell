/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 00:31:37 by ilyas-guney       #+#    #+#             */
/*   Updated: 2025/08/19 00:34:35 by ilyas-guney      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_or_add(t_env **env, char *key, char *val, char *arg)
{
	t_env	*cur;
	t_env	*node;

	cur = *env;
	while (cur && ft_strcmp(cur->key, key))
		cur = cur->next;
	if (cur)
	{
		free(cur->value);
		cur->value = val;
		free(key);
		return ;
	}
	node = new_env_node(arg);
	if (!node)
		return ;
	if (!*env)
		*env = node;
	else
	{
		cur = *env;
		while (cur->next)
			cur = cur->next;
		cur->next = node;
	}
}

static t_env	*find_min(t_env *env, t_env *last)
{
	t_env	*min;
	t_env	*cur;

	min = NULL;
	cur = env;
	while (cur)
	{
		if ((!last || ft_strcmp(cur->key, last->key) > 0)
			&& (!min || ft_strcmp(cur->key, min->key) < 0))
			min = cur;
		cur = cur->next;
	}
	return (min);
}

int	builtin_print_export(t_env *env)
{
	t_env	*last;
	t_env	*min;

	last = NULL;
	while ((min = find_min(env, last)))
	{
		printf("declare -x %s", min->key);
		if (min->value && min->value[0])
			printf("=\"%s\"", min->value);
		printf("\n");
		last = min;
	}
	return (0);
}

int	builtin_export(t_env **env, t_cmd *cmd)
{
	int		i;
	char	*key;
	char	*val;

	if (!cmd->argv[1])
		return (builtin_print_export(*env));
	i = 1;
	while (cmd->argv[i])
	{
		key = ft_substr(cmd->argv[i], 0, ft_strchr(cmd->argv[i], '=') - cmd->argv[i]);
		val = ft_strchr(cmd->argv[i], '=') ? ft_strdup(ft_strchr(cmd->argv[i], '=') + 1) : ft_strdup("");
		update_or_add(env, key, val, cmd->argv[i]);
		i++;
	}
	return (0);
}
