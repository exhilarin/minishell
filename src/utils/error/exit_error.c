/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 04:06:54 by iguney            #+#    #+#             */
/*   Updated: 2025/08/28 04:06:56 by iguney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_status_manager(int status, int mode)
{
	static int	exit_status = 0;

	if (mode == 1)
		exit_status = status;
	return (exit_status);
}

int	shutdown_shell(t_shell *shell)
{
	int	status;

	if (!shell)
		return (1);
	status = exit_status_manager(0, 0);
	if (shell->env)
	{
		free_env(shell->env);
		shell->env = NULL;
	}
	free_all(shell);
	return (status);
}

void	exit_shell(int code, char *msg)
{
	t_shell	*shell;

	if (msg)
		ft_putstr_fd(msg, STDERR_FILENO);
	exit_status_manager(code, 1);
	shell = set_get_shell(NULL);
	if (shell)
		exit(shutdown_shell(shell));
	exit(code);
}

void	exec_error(t_shell *shell, t_cmd *cmd)
{
	if (shell->exec->flag == 1)
		handle_flag_error(cmd);
	else if (!shell->exec->cmd_path)
		handle_no_cmd_path(cmd);
	else if (access(shell->exec->cmd_path, X_OK) != 0)
		handle_access_error(shell, cmd);
}

void	print_error(char *msg, int code)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	exit_status_manager(code, 1);
}
