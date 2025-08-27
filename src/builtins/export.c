/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 00:31:37 by ilyas-guney       #+#    #+#             */
/*   Updated: 2025/08/27 23:24:46 by mugenan          ###   ########.fr       */
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

static void	handle_export_value(t_shell *shell, char *key, char *arg)
{
	char	*val;
	t_env	*var;

	val = ms_val_from_arg(arg);
	if (ms_has_plus_equal(arg))
	{
		var = ms_export_get(shell->env, key);
		if (var && var->value)
			val = ms_strjoin_free(ft_strdup(var->value), val);
	}
	ms_export_set(&shell->env, key, val);
	free(val);
}

static int	process_export_arg(t_shell *shell, char *arg)
{
	char	*key;
	t_env	*existing_var;

	if (!ms_is_valid_key(arg))
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
		return (1);
	}
	key = ms_key_from_arg(arg);
	if (ms_has_plus_equal(arg) || ft_strchr(arg, '='))
		handle_export_value(shell, key, arg);
	else
	{
		// Değişken zaten varsa değerini koru, yoksa NULL ile oluştur
		existing_var = ms_export_get(shell->env, key);
		if (existing_var)
		{
			// Değişken zaten export edilmiş, değerini değiştirme
			// Sadece export durumunu koru (zaten export edilmiş)
		}
		else
		{
			// Yeni değişken oluştur, değer olmadan
			ms_export_set(&shell->env, key, NULL);
		}
	}
	free(key);
	return (0);
}

void	builtin_export(t_shell *shell, t_cmd *cmd)
{
	int	i;
	int	status;

	if (!cmd->argv[1])
	{
		builtin_print_export(shell->env);
		return ;
	}
	i = 1;
	status = 0;
	while (cmd->argv[i])
	{
		if (process_export_arg(shell, cmd->argv[i]))
			status = 1;
		i++;
	}
	exit_status_manager(status, 1);
}
