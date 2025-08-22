/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 00:22:09 by ilyas-guney       #+#    #+#             */
/*   Updated: 2025/08/23 01:01:44 by ilyas-guney      ###   ########.fr       */
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
	rl_clear_history();
	shell = NULL;
	return (status);
}

void	print_error(char *msg, t_shell *shell, int code)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	shell->exit_status = code;
}

