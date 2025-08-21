/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 04:22:09 by mugenan           #+#    #+#             */
/*   Updated: 2025/08/22 01:56:19 by ilyas-guney      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_special_case(t_shell *shell, t_cmd *cmd, t_redir *redir)
{
	if (!cmd && redir)
	{
		handle_redirections(shell, redir, 1);
		return (free_all(shell));
	}
	if (cmd && !cmd->next)
	{
		if (is_builtin(cmd))
		{
			shell->exit_status = exec_builtin_with_redir(shell, cmd);
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

char	*get_cmd_path(t_shell *shell, t_cmd *cmd)
{
	char	*tmp;
	char	*full;
	char	*cmd_name;
	int		i;

	cmd_name = cmd->argv[0];
	if (ft_strchr(cmd_name, '/') && access(cmd_name, X_OK) == 0)
		return (ft_strdup(cmd_name));
	shell->exec->paths = ft_split(get_env_value(shell->env, "PATH"), ':');
	if (!shell->exec->paths)
		return (NULL);
	i = -1;
	while (shell->exec->paths[++i])
	{
		tmp = ft_strjoin(shell->exec->paths[i], "/");
		full = ft_strjoin(tmp, cmd_name);
		free(tmp);
		if (access(full, X_OK) == 0)
			return (full);
		free(full);
	}
	return (NULL);
}
