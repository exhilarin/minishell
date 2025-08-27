/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 02:16:45 by ilyas-guney       #+#    #+#             */
/*   Updated: 2025/08/27 22:37:56 by mugenan          ###   ########.fr       */
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

void	free_exec(t_exec *exec)
{
	if (!exec)
		return ;
	if (exec->cmd_path)
	{
		free(exec->cmd_path);
		exec->cmd_path = NULL;
	}
	if (exec->paths)
	{
		free_char_array(exec->paths);
		exec->paths = NULL;
	}
	if (exec->envp)
	{
		free_char_array(exec->envp);
		exec->envp = NULL;
	}
	free(exec);
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		if (env->env_line)
			free(env->env_line);
		if (env->key)
			free(env->key);
		if (env->value)
			free(env->value);
		free(env);
		env = tmp;
	}
}
