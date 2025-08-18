/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 23:16:40 by mugenan           #+#    #+#             */
/*   Updated: 2025/08/18 08:09:40 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_env *env)
{
	while (env)
	{
		if (env->value && env->value[0])
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}
