/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 20:25:38 by iguney            #+#    #+#             */
/*   Updated: 2025/08/17 09:57:51 by ilyas-guney      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*parser(t_token *tokens)
{
	t_cmd	*commands;
	t_cmd	*current_cmd;
	t_token	*current_token;

	commands = NULL;
	current_cmd = init_cmd();
	if (!current_cmd)
		return (NULL);
	current_token = tokens;
	while (current_token)
	{
		if (!process_token(&current_token, &current_cmd, &commands))
			return (free_cmd(current_cmd), NULL);
		current_token = current_token->next;
	}
	add_cmd_to_lst(&commands, current_cmd);
	return (commands);
}

int	process_token(t_token **c_tkn, t_cmd **c_cmd, t_cmd **cmds)
{
	char	*marked_value;

	if ((*c_tkn)->type == WORD)
	{
		if ((*c_tkn)->quoted == 1)
		{
			marked_value = ft_strjoin("\001", (*c_tkn)->value);
			add_arg_to_cmd(*c_cmd, marked_value);
			free(marked_value);
		}
		else
			add_arg_to_cmd(*c_cmd, (*c_tkn)->value);
	}
	else if ((*c_tkn)->type == REDIR_IN || (*c_tkn)->type == REDIR_OUT
		|| (*c_tkn)->type == APPEND || (*c_tkn)->type == HEREDOC)
	{
		add_redir_to_cmd(*c_cmd, (*c_tkn)->type, (*c_tkn)->next->value);
		*c_tkn = (*c_tkn)->next;
	}
	else if ((*c_tkn)->type == PIPE)
	{
		add_cmd_to_lst(cmds, *c_cmd);
		*c_cmd = init_cmd();
		if (!(*c_cmd))
			return (0);
	}
	return (1);
}
