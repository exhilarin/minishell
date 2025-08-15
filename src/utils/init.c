/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 06:55:45 by iguney            #+#    #+#             */
/*   Updated: 2025/08/15 06:47:01 by iguney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_shell *shell)
{
	shell->exit_status = 0;
	shell->token_list = NULL;
	shell->command_list = NULL;
	shell->env = NULL;
	shell->exec = NULL;
}

void	init_env(t_shell *shell, char **envp)
{
	t_env	*new;
	t_env	*last;
	int		i;

	shell->env = NULL;
	i = 0;
	while (envp[i])
	{
		new = new_env_node(envp[i]);
		if (!new)
			return ;
		if (!shell->env)
			shell->env = new;
		else
		{
			last = shell->env;
			while (last->next)
				last = last->next;
			last->next = new;
		}
		i++;
	}
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
	exec->cmd_path = NULL;
	exec->paths = NULL;
	exec->envp = NULL;
	return (exec);
}
