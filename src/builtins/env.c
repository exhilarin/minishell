/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 23:16:40 by mugenan           #+#    #+#             */
/*   Updated: 2025/08/23 01:22:35 by ilyas-guney      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_env(t_env *env)
{
	while (env)
	{
		if (env->value && env->value[0])
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}
