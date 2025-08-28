/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 21:34:43 by mugenan           #+#    #+#             */
/*   Updated: 2025/08/28 04:04:55 by iguney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	backup_fds(int *stdin_bak, int *stdout_bak)
{
	*stdin_bak = dup(STDIN_FILENO);
	*stdout_bak = dup(STDOUT_FILENO);
	if (*stdin_bak == -1 || *stdout_bak == -1)
	{
		if (*stdin_bak != -1)
			close(*stdin_bak);
		if (*stdout_bak != -1)
			close(*stdout_bak);
		exit_status_manager(1, 1);
		return (0);
	}
	return (1);
}

static void	restore_fds(int stdin_bak, int stdout_bak)
{
	if (dup2(stdin_bak, STDIN_FILENO) == -1
		|| dup2(stdout_bak, STDOUT_FILENO) == -1)
		exit_status_manager(1, 1);
	close(stdin_bak);
	close(stdout_bak);
}

void	exec_builtin_with_redir(t_shell *shell, t_cmd *cmd)
{
	int	stdin_bak;
	int	stdout_bak;

	if (!backup_fds(&stdin_bak, &stdout_bak))
		return ;
	handle_redirections(shell, cmd->redir, 1);
	if (exit_status_manager(0, 0) == 130)
	{
		restore_fds(stdin_bak, stdout_bak);
		exit_status_manager(1, 1);
		return ;
	}
	exec_builtin(shell, cmd);
	restore_fds(stdin_bak, stdout_bak);
}
