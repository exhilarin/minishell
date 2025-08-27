/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:19:20 by iguney            #+#    #+#             */
/*   Updated: 2025/08/27 20:55:25 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <sys/types.h>
# include <sys/stat.h>

#include "minishell.h"

typedef struct s_shell	t_shell;

typedef struct s_exec
{
	int		flag;
	char	*cmd_path;
	char	**paths;
	char	**envp;
}	t_exec;

char	*get_cmd_path(t_shell *shell, t_cmd *cmd);

void	executor(t_shell *shell, t_cmd *cmd);
void	exec_builtin_with_redir(t_shell *shell, t_cmd *cmd);
void	handle_redirections(t_shell *shell, t_redir *redir, int proccess);

int		redir_heredoc(t_shell *shell, t_redir *redir);
int		handle_heredoc(t_shell *shell, t_redir *redir);
int		check_special_case(t_shell *shell, t_cmd *cmd, t_redir *redir);

#endif