/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 06:51:59 by mugenan           #+#    #+#             */
/*   Updated: 2025/08/16 07:14:32 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	read_heredoc(t_redir *redir, int write_fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, redir->file) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, write_fd);
		free(line);
	}
}

void	redir_heredoc(t_shell *shell, t_redir *redir, int *heredoc_fd)
{
	int	fd[2];

	if (pipe(fd) == -1)
	{
		perror("minishell: pipe");
		shell->exit_status = 1;
		exit(shutdown_shell(shell));
	}
	read_heredoc(redir, fd[1]);
	close(fd[1]);
	*heredoc_fd = fd[0];
}
