/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 02:16:45 by ilyas-guney       #+#    #+#             */
/*   Updated: 2025/08/27 21:00:16 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_all(t_shell *shell)
{
	if (!shell)
		return (1);
	if (shell->input)
	{
		free(shell->input);
		shell->input = NULL;
	}
	if (shell->token_list)
	{
		free_tokens(shell->token_list);
		shell->token_list = NULL;
	}
	if (shell->command_list)
	{
		free_cmd(shell->command_list);
		shell->command_list = NULL;
	}
	if (shell->exec)
	{
		free_exec(shell->exec);
		shell->exec = NULL;
	}
	return (0);
}

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		if (tokens->value)
			free(tokens->value);
		free (tokens);
		tokens = tmp;
	}
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->argv)
		{
			i = 0;
			while (cmd->argv[i])
			{
				free(cmd->argv[i]);
				i++;
			}
			free(cmd->argv);
		}
		if (cmd->redir)
			free_redir(cmd->redir);
		free(cmd);
		cmd = tmp;
	}
}

void	free_redir(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir->next;
		if (redir->file)
			free(redir->file);
		free(redir);
		redir = tmp;
	}
}

void	free_envp(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return ;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}
