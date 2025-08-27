/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 03:55:36 by iguney            #+#    #+#             */
/*   Updated: 2025/08/27 21:01:40 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal_code = 0;

static void	signal_handler(int sig)
{
	(void)sig;
	if (g_signal_code == 0)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (g_signal_code == 1)
	{
		write(STDOUT_FILENO, "\n", 1);
		exit_status_manager(130, 1);
	}
	else if (g_signal_code == 2)
	{
		write(STDOUT_FILENO, "\n", 1);
		exit_shell(130, NULL);
	}
}

void	init_signal(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	discard_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	wait_and_set_status(pid_t *pids, int count)
{
	int	i;
	int	status;

	i = 0;
	while (i < count)
	{
		waitpid(pids[i], &status, 0);
		i++;
	}
	if (WIFEXITED(status))
		exit_status_manager(WEXITSTATUS(status), 1);
	else if (WIFSIGNALED(status))
		exit_status_manager(128 + WTERMSIG(status), 1);
}
