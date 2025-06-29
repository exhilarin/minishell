/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:13:23 by ilyas-guney       #+#    #+#             */
/*   Updated: 2025/06/30 01:22:18 by ilyas-guney      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*parser(t_token *tokens)
{
	t_token	*token;
	t_cmd	*commands;
	t_cmd	*current_cmd;

	token = tokens;
	void *(token);
	commands = NULL;
	current_cmd = init_cmd();
	while (token)
	{
		if (!process_token(&token, &current_cmd, &commands, tokens))
			return (NULL);
		token = token->next;
	}
	add_cmd_to_lst(&commands, current_cmd);
	return (commands);
}

int	process_token(t_token **token, t_cmd **cmd, t_cmd **cmds, t_token *tokens)
{
	if ((*token)->type == WORD || (*token)->type == QUOTE_SINGLE
		|| (*token)->type == QUOTE_DOUBLE)
		add_arg_to_cmd(*cmd, (*token)->value);
	else if ((*token)->type == REDIR_IN || (*token)->type == REDIR_OUT
		|| (*token)->type == APPEND || (*token)->type == HEREDOC)
	{
		add_redir_to_cmd(*cmd, (*token)->type, (*token)->next->value);
		*token = (*token)->next;
	}
	else if ((*token)->type == PIPE)
	{
		add_cmd_to_lst(cmds, *cmd);
		*cmd = init_cmd();
	}
	return (1);
}

// init_cmd();

// add_arg_to_cmd();

// add_redir_to_cmd();

// add_cmd_to_list();