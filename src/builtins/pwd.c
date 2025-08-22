/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 00:50:31 by ilyas-guney       #+#    #+#             */
/*   Updated: 2025/08/23 01:26:18 by ilyas-guney      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"

void	builtin_pwd(t_shell *shell)
{
	char	cwd[PATH_MAX];

	if (!getcwd(cwd, sizeof(cwd)))
	{
		print_error("minishell: pwd: getcwd failed\n", shell, 1);
		return ;
	}
	ft_putendl_fd(cwd, STDOUT_FILENO);
}

