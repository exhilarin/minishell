/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 00:31:37 by ilyas-guney       #+#    #+#             */
/*   Updated: 2025/08/23 17:59:59 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	builtin_print_export(t_env *env)
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
}

static int	update_env(t_env **env, t_env *node)
{
	t_env	*curr;

	if (!env || !*env || !node)
		return (0);
	curr = *env;
	while (curr)
	{
		if (!ft_strcmp(curr->key, node->key))
		{
			if (curr->value)
				free(curr->value);
			curr->value = node->value;
			if (curr->env_line)
				free(curr->env_line);
			curr->env_line = ft_strdup(node->env_line);
			free(node->key);
			free(node->env_line);
			free(node);
			return (1);
		}
		curr = curr->next;
	}
	return (0);
}

static void	append_env_node(t_env **env, t_env *node)
{
	t_env	*current;

	if (!*env)
	{
		*env = node;
		return ;
	}
	current = *env;
	while (current->next)
		current = current->next;
	current->next = node;
}

void	builtin_export(t_shell *shell, t_cmd *cmd)
{
	t_env	*node;
	int		i;

	if (!cmd->argv[1])
	{
		builtin_print_export(shell->env);
		return ;
	}
	i = 1;
	while (cmd->argv[i])
	{
		node = new_env_node(cmd->argv[i]);
		if (!node)
		{
			print_error("minishell: export: allocation failed\n", shell, 1);
			return ;
		}
		if (!update_env(&shell->env, node))
			append_env_node(&shell->env, node);
		i++;
	}
}

