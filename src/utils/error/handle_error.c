/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 23:11:12 by mugenan           #+#    #+#             */
/*   Updated: 2025/08/27 23:13:46 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_flag_error(t_cmd *cmd)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd->argv[0], STDERR_FILENO);
	ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	exit_shell(1, NULL);
}

void	handle_no_cmd_path(t_cmd *cmd)
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

void	handle_access_error(t_shell *shell, t_cmd *cmd)
{
	(void)shell;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd->argv[0], STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
	exit_shell(126, NULL);
}
