/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:13:23 by ilyas-guney       #+#    #+#             */
/*   Updated: 2025/06/30 01:48:20 by ilyas-guney      ###   ########.fr       */
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
		return (0);
	current_token = tokens;
	while (current_token)
	{
		if (!process_token(&current_token, &current_cmd, &commands, tokens))
			return (NULL);
		current_token = current_token->next;
	}
	add_cmd_to_lst(&commands, current_cmd);
	return (commands);
}

int	process_token(t_token **c_tkn, t_cmd **c_cmd, t_cmd **cmds, t_token *tkns)
{
	if ((*c_tkn)->type == WORD || (*c_tkn)->type == QUOTE_SINGLE
		|| (*c_tkn)->type == QUOTE_DOUBLE)
		add_arg_to_cmd(*c_cmd, (*c_tkn)->value);
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

// void	add_arg_to_cmd(t_cmd *current_cmd, char *token_value)
// {
// 	if (!current_cmd->argv)
// 		current_cmd->argv = token_value;
// 	else
// 	{
// 		while (token_value)
			
// 	}	
// }

// add_redir_to_cmd();

// add_cmd_to_list();