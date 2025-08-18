/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 04:22:09 by mugenan           #+#    #+#             */
/*   Updated: 2025/08/18 04:35:56 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_special_case(t_shell *shell, t_redir *redir)
{
	if (!shell->command_list && redir)
	{
		handle_redirections(shell, redir, 1);
		return (free_all(shell));
	}
	if (shell->command_list && !shell->command_list->next)
	{
		if (is_builtin(shell->command_list))
		{
			shell->exit_status = exec_builtin_with_redir(shell);
			return (shell->exit_status);
		}
	}
	return (-1);
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

char	*get_cmd_path(t_shell *shell)
{
	char	*tmp;
	char	*full;
	char	*cmd;
	int		i;

	cmd = shell->command_list->argv[0];
	if (ft_strchr(cmd, '/') && access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	shell->exec->paths = ft_split(get_env_value(shell->env, "PATH"), ':');
	if (!shell->exec->paths)
		return (NULL);
	i = -1;
	while (shell->exec->paths[++i])
	{
		tmp = ft_strjoin(shell->exec->paths[i], "/");
		full = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full, X_OK) == 0)
			return (full);
		free(full);
	}
	return (NULL);
}
