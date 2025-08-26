/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 00:50:31 by ilyas-guney       #+#    #+#             */
/*   Updated: 2025/08/26 18:09:07 by mugenan          ###   ########.fr       */
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
