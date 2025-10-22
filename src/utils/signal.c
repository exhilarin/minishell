/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 03:55:36 by iguney            #+#    #+#             */
/*   Updated: 2025/08/28 07:52:56 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal_code = 0;

void	signal_handler(int sig)
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

void	sigquit_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "Quit (core dumped)", 18);
	write(STDOUT_FILENO, "\n", 1);
	exit_shell(131, NULL);
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
	int	last_status;

	last_status = 0;
	i = 0;
	while (i < count)
	{
		if (waitpid(pids[i], &status, 0) > 0)
			last_status = status;
		i++;
	}
	if (count == 0)
		return ;
	if (WIFSIGNALED(last_status))
	{
		if (WTERMSIG(last_status) == SIGQUIT)
			ft_putendl_fd("Quit (core dumped)", STDERR_FILENO);
		else if (WTERMSIG(last_status) == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
		exit_status_manager(128 + WTERMSIG(last_status), 1);
	}
	else if (WIFEXITED(last_status))
		exit_status_manager(WEXITSTATUS(last_status), 1);
}
