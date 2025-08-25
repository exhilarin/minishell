/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 03:55:36 by iguney            #+#    #+#             */
/*   Updated: 2025/08/26 01:42:13 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal_code = 0;

void	signal_handler(int sig)
{
	(void)sig;
	if (g_signal_code == 0) // normal prompt
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_signal_code = 130;
	}
	else if (g_signal_code == 1) // komut çalışırken
	{
		write(1, "\n", 1);
		g_signal_code = 130;
	}
	else if (g_signal_code == 2) // heredoc modunda
	{
		write(1, "\n", 1);
		exit_shell(130);
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
