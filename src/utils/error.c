/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 00:22:09 by ilyas-guney       #+#    #+#             */
/*   Updated: 2025/08/26 02:11:36 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	shutdown_shell(t_shell *shell)
{
	int	status;

	if (!shell)
		return (1);
	status = shell->exit_status;
	free_all(shell);
	if (shell->env)
	{
		free_env(shell->env);
		shell->env = NULL;
	}
	shell = NULL;
	return (status);
}

void	print_error(char *msg, t_shell *shell, int code)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	shell->exit_status = code;
}

void	exit_shell(int code, char *msg)
{
    t_shell *shell = set_get_shell(NULL);

    if (msg)
        ft_putstr_fd(msg, STDERR_FILENO);

    if (shell)
        shutdown_shell(shell);

    exit(code);
}
