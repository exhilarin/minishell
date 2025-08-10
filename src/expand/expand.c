/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 09:01:22 by iguney            #+#    #+#             */
/*   Updated: 2025/08/10 17:23:25 by iguney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	var_expand(t_shell *shell)
{
	t_cmd	*cmd;

	if (!shell)
		return ;
	cmd = shell->command_list;
	while (cmd)
	{
		expand_cmd_args(shell, cmd);
		expand_redirections(shell, cmd);
		cmd = cmd->next;
	}
}

void	expand_cmd_args(t_shell *shell, t_cmd *cmd)
{
	int		i;
	char	*expanded;

	if (!cmd || !cmd->argv)
		return ;
	i = 0;
	while (cmd->argv[i])
	{
		expanded = expand_arg(shell, cmd->argv[i], 0);
		if (expanded)
		{
			free(cmd->argv[i]);
			cmd->argv[i] = expanded;
		}
		i++;
	}
}

void	expand_redirections(t_shell *shell, t_cmd *cmd)
{
	t_redir	*redir;
	char	*expanded;

	if (!cmd)
		return ;
	redir = cmd->redir;
	while (redir)
	{
		if (redir->type != HEREDOC && redir->file)
		{
			expanded = expand_arg(shell, redir->file, 1);
			if (expanded)
			{
				free(redir->file);
				redir->file = expanded;
			}
		}
		redir = redir->next;
	}
}

char	*expand_arg(t_shell *shell, char *arg, int is_redirection)
{
	if (is_redirection && is_heredoc_arg(arg))
		return (ft_strdup(arg));
	if (is_single_quoted(arg))
		return (remove_single_quotes(arg));
	if (is_double_quoted(arg))
		return (expand_dquotes(shell, arg));
	return (expand_unquoted(shell, arg));
}
