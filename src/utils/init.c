/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 06:55:45 by iguney            #+#    #+#             */
/*   Updated: 2025/08/27 22:41:02 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_shell *shell)
{
	shell->in_fd = -1;
	shell->heredoc_fd = -1;
	shell->token_list = NULL;
	shell->command_list = NULL;
	shell->env = NULL;
	shell->exec = NULL;
}

void	init_env(t_shell *shell, char **envp)
{
	t_env	*new;
	t_env	*current;
	int		i;

	shell->env = NULL;
	i = -1;
	while (envp[++i])
	{
		new = new_env_node(envp[i]);
		if (!new)
		{
			free_env(shell->env);
			shell->env = NULL;
			return ;
		}
		if (!shell->env)
			shell->env = new;
		else
		{
			current = shell->env;
			while (current->next)
				current = current->next;
			current->next = new;
		}
	}
}

t_env	*init_env_node(void)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->env_line = NULL;
	node->key = NULL;
	node->value = NULL;
	node->next = NULL;
	return (node);
}

t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->redir = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_exec	*init_exec(void)
{
	t_exec	*exec;

	exec = malloc(sizeof(t_exec));
	if (!exec)
		return (NULL);
	exec->cmd_path = NULL;
	exec->paths = NULL;
	exec->envp = NULL;
	exec->flag = 0;
	return (exec);
}
