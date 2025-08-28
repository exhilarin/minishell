/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 04:06:41 by iguney            #+#    #+#             */
/*   Updated: 2025/08/28 04:06:43 by iguney           ###   ########.fr       */
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

static void	handle_word_token_parse(t_token *token, t_cmd *cmd)
{
	char	*marked_value;

	if (token->quoted == 1)
	{
		marked_value = ft_strjoin("\001", token->value);
		add_arg_to_cmd(cmd, marked_value);
		free(marked_value);
	}
	else
		add_arg_to_cmd(cmd, token->value);
}

static void	handle_redir_token_parse(t_token **c_tkn, t_cmd *cmd)
{
	add_redir_to_cmd(cmd, (*c_tkn)->type, (*c_tkn)->next->value);
	*c_tkn = (*c_tkn)->next;
}

static int	handle_pipe_token_parse(t_cmd **c_cmd, t_cmd **cmds)
{
	add_cmd_to_lst(cmds, *c_cmd);
	*c_cmd = init_cmd();
	if (!(*c_cmd))
		return (0);
	return (1);
}

int	process_token(t_token **c_tkn, t_cmd **c_cmd, t_cmd **cmds)
{
	if ((*c_tkn)->type == WORD)
		handle_word_token_parse(*c_tkn, *c_cmd);
	else if ((*c_tkn)->type == REDIR_IN || (*c_tkn)->type == REDIR_OUT
		|| (*c_tkn)->type == APPEND || (*c_tkn)->type == HEREDOC)
		handle_redir_token_parse(c_tkn, *c_cmd);
	else if ((*c_tkn)->type == PIPE)
	{
		if (!handle_pipe_token_parse(c_cmd, cmds))
			return (0);
	}
	return (1);
}
