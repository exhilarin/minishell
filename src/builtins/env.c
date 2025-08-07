/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 23:16:40 by mugenan           #+#    #+#             */
/*   Updated: 2025/08/07 03:19:45 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_env *env)
{
	while (env)
	{
		if (env->value && env->value[0])
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
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

void	print_env_sorted(t_env *env)
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
