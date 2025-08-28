/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 04:05:41 by iguney            #+#    #+#             */
/*   Updated: 2025/08/28 04:05:42 by iguney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_pwd(void)
{
	char	cwd[PATH_MAX];

	if (!getcwd(cwd, sizeof(cwd)))
	{
		print_error("minishell: pwd: getcwd failed\n", 1);
		return ;
	}
	ft_putendl_fd(cwd, STDOUT_FILENO);
	exit_status_manager(0, 1);
}
