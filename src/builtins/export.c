/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 00:31:37 by ilyas-guney       #+#    #+#             */
/*   Updated: 2025/08/26 17:54:10 by mugenan          ###   ########.fr       */
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
		if (min->value)
		{
			if (min->value[0])
				printf("=\"%s\"", min->value);
			else
				printf("=\"\"");
		}
		printf("\n");
		last_min = min;
	}
	exit_status_manager(0, 1);
}

static t_env	*ms_export_get(t_env *env, char *key)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env);
		env = env->next;
	}
	return (NULL);
}

static void	ms_export_set(t_env **env, char *key, char *value)
{
	t_env	*curr;
	t_env	*new_node;

	curr = ms_export_get(*env, key);
	if (curr)
	{
		if (curr->value)
			free(curr->value);
		curr->value = value ? ft_strdup(value) : NULL;
		if (curr->env_line)
			free(curr->env_line);
		if (value)
			curr->env_line = ms_join_kv(key, value);
		else
			curr->env_line = NULL;
		return ;
	}
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return ;
	new_node->key = ft_strdup(key);
	new_node->value = value ? ft_strdup(value) : NULL;
	new_node->env_line = value ? ms_join_kv(key, value) : NULL;
	new_node->next = NULL;
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

static void	ms_export_print_error(char *arg)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
}

void	builtin_export(t_shell *shell, t_cmd *cmd)
{
	int		i;
	int		status;
	char	*key;
	char	*val;
	t_env	*var;

	if (!cmd->argv[1])
	{
		builtin_print_export(shell->env);
		return ;
	}
	i = 1;
	status = 0;
	while (cmd->argv[i])
	{
		if (!ms_is_valid_key(cmd->argv[i]))
		{
			ms_export_print_error(cmd->argv[i]);
			status = 1;
			i++;
			continue ;
		}
		key = ms_key_from_arg(cmd->argv[i]);
		if (ms_has_plus_equal(cmd->argv[i]) || ft_strchr(cmd->argv[i], '='))
		{
			val = ms_val_from_arg(cmd->argv[i]);
			if (ms_has_plus_equal(cmd->argv[i]))
			{
				var = ms_export_get(shell->env, key);
				if (var && var->value)
					val = ms_strjoin_free(ft_strdup(var->value), val);
			}
			ms_export_set(&shell->env, key, val);
			free(val);
		}
		else
		{
			ms_export_set(&shell->env, key, NULL);
		}
		free(key);
		i++;
	}
	exit_status_manager(status, 1);
}
