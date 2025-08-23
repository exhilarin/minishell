/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 04:22:09 by mugenan           #+#    #+#             */
/*   Updated: 2025/08/23 19:07:45 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_special_case(t_shell *shell, t_cmd *cmd, t_redir *redir)
{
	if (!cmd && redir)
	{
		handle_redirections(shell, redir, 1);
		free_all(shell);
		return (1);
	}
	else if ((cmd && !cmd->next) && is_builtin(cmd))
	{
		exec_builtin_with_redir(shell, cmd);
		return (1);
	}
	return (0);
}

void	handle_heredoc(t_shell *shell, t_redir *redir)
{
	while (redir)
	{
		if (redir->type == HEREDOC)
			redir_heredoc(shell, redir);
		redir = redir->next;
	}
}

static	void split_path(t_shell *shell)
{
	char	*path_line;

	path_line = NULL;
	path_line = get_env_value(shell->env, "PATH");
	if(!path_line)
	{
		shell->exec->flag = 1;
		return ;
	}
	shell->exec->paths = ft_split(path_line, ':');
}

static char	*search_in_paths(t_shell *shell, char *cmd_name)
{
	int			i;
	char		*tmp;
	char		*full;
	struct stat	st;

	i = -1;
	while (shell->exec->paths[++i])
	{
		tmp = ft_strjoin(shell->exec->paths[i], "/");
		full = ft_strjoin(tmp, cmd_name);
		free(tmp);
		if (access(full, X_OK) == 0
			&& stat(full, &st) == 0
			&& S_ISREG(st.st_mode))
			return (full);
		free(full);
	}
	return (NULL);
}

char	*get_cmd_path(t_shell *shell, t_cmd *cmd)
{
	struct stat	st;
	char		*cmd_name;

	cmd_name = cmd->argv[0];
	if (ft_strchr(cmd_name, '/'))
	{
		if (access(cmd_name, X_OK) == 0
			&& stat(cmd_name, &st) == 0
			&& S_ISREG(st.st_mode))
			return (ft_strdup(cmd_name));
		return (NULL);
	}
	split_path(shell);
	if (!shell->exec->paths)
		return (NULL);
	return (search_in_paths(shell, cmd_name));
}
