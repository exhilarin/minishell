/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 00:22:09 by ilyas-guney       #+#    #+#             */
/*   Updated: 2025/08/24 23:50:26 by mugenan          ###   ########.fr       */
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

t_shell	*set_get_shell(t_shell *sh)
{
	static t_shell	*stored;

	if (sh)
		stored = sh;
	return (stored);
}

void	print_error(char *msg, t_shell *shell, int code)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	shell->exit_status = code;
}

void	exit_shell(int code)
{
	t_shell	*sh;

	sh = set_get_shell(NULL);
	if (sh)
	{
		sh->exit_status = code;
		shutdown_shell(sh);
	}
	exit(code);
}
