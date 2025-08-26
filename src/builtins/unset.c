/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 08:21:04 by mugenan           #+#    #+#             */
/*   Updated: 2025/08/26 17:55:03 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	delete_node(t_env **head, t_env *prev, t_env *current)
{
	if (prev)
		prev->next = current->next;
	else
		*head = current->next;
	free(current->env_line);
	free(current->key);
	free(current->value);
	free(current);
}

void	builtin_unset(t_env **env, t_cmd *cmd)
{
	t_env	*current;
	t_env	*prev;
	int		i;

	i = 1;
	while (cmd->argv[i])
	{
		prev = NULL;
		current = *env;
		while (current)
		{
			if (ft_strcmp(current->key, cmd->argv[i]) == 0)
			{
				delete_node(env, prev, current);
				break ;
			}
			prev = current;
			current = current->next;
		}
		i++;
	}
	exit_status_manager(0, 1);
}
