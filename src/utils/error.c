/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 00:22:09 by ilyas-guney       #+#    #+#             */
/*   Updated: 2025/08/26 17:56:16 by mugenan          ###   ########.fr       */
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
	free_all(shell);
	if (shell->env)
	{
		free_env(shell->env);
		shell->env = NULL;
	}
	shell = NULL;
	return (status);
}

void	print_error(char *msg, int code)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	exit_status_manager(code, 1);
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

static void	handle_flag_error(t_cmd *cmd)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd->argv[0], STDERR_FILENO);
	ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	exit_shell(1, NULL);
}

static void	handle_no_cmd_path(t_cmd *cmd)
{
	if (ft_strchr(cmd->argv[0], '/'))
	{
		ft_putstr_fd(cmd->argv[0], STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		exit_shell(127, NULL);
	}
	else
	{
		ft_putstr_fd(cmd->argv[0], STDERR_FILENO);
		exit_shell(127, ": command not found\n");
	}
}

static void	handle_access_error(t_shell *shell, t_cmd *cmd)
{
	(void)shell;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd->argv[0], STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
	exit_shell(126, NULL);
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
