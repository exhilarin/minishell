/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 20:25:01 by iguney            #+#    #+#             */
/*   Updated: 2025/08/16 20:25:25 by iguney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_token(t_token **tokens, t_token_type type, char *value)
{
	t_token	*new_token;
	t_token	*current;

	if (!ft_strlen(value))
	{
		free(value);
		return ;
	}
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (free_tokens(*tokens), free(value));
	new_token->type = type;
	new_token->value = value;
	new_token->next = NULL;
	if (!*tokens)
		*tokens = new_token;
	else
	{
		current = *tokens;
		while (current->next)
			current = current->next;
		current->next = new_token;
	}
}

void	add_arg_to_cmd(t_cmd *current_cmd, char *token_value)
{
	int		argc;
	char	**new_argv;
	int		i;

	if (!current_cmd || !token_value)
		return ;
	argc = 0;
	if (current_cmd->argv)
		while (current_cmd->argv[argc])
			argc++;
	new_argv = create_new_argv(current_cmd->argv, token_value, argc);
	if (!new_argv)
		return ;
	if (current_cmd->argv)
	{
		i = 0;
		while (current_cmd->argv[i])
			free(current_cmd->argv[i++]);
		free(current_cmd->argv);
	}
	current_cmd->argv = new_argv;
}

void	add_redir_to_cmd(t_cmd *cmd, int type, char *file)
{
	t_redir	*tmp;
	t_redir	*new_redir;

	if (!file)
		return ;
	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return ;
	new_redir->type = type;
	new_redir->file = ft_strdup(file);
	if (!new_redir->file)
	{
		free(new_redir);
		return ;
	}
	new_redir->next = NULL;
	if (!cmd->redir)
		cmd->redir = new_redir;
	else
	{
		tmp = cmd->redir;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_redir;
	}
}

void	add_cmd_to_lst(t_cmd **cmds, t_cmd *new_cmd)
{
	t_cmd	*tmp;

	if (!cmds || !new_cmd)
		return ;
	if (!*cmds)
	{
		*cmds = new_cmd;
		return ;
	}
	tmp = *cmds;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_cmd;
}
