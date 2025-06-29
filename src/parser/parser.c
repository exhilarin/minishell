/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:13:23 by ilyas-guney       #+#    #+#             */
/*   Updated: 2025/06/29 19:58:32 by ilyas-guney      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*parser(t_token *tokens)
{
	if (!validate_syntax(tokens))
		return (syntax_error("syntax error"));

	t_cmd	*commands = NULL;
	t_cmd	*current_cmd = init_cmd(); // aktif komut
	t_token	*current = tokens;
	while (current)
	{
		if (current->type == WORD ||
			current->type == QUOTE_SINGLE || current->type == QUOTE_DOUBLE)
				add_arg_to_cmd(current_cmd, current->value); // argv'ye ekle
		else if (current->type == REDIR_IN || current->type == REDIR_OUT ||
				current->type == APPEND || current->type == HEREDOC)
		{
			if (!current->next)
				return (syntax_error("unexpected end of redirect"));
			add_redir_to_cmd(current_cmd, current->type, current->next->value);
			current = current->next; // filename atla
		}
		else if (current->type == PIPE)
		{
			append_cmd(&commands, current_cmd); // önceki komutu listeye ekle
			current_cmd = init_cmd();           // yeni komut başlat
		}
		current = current->next;
	}
	append_cmd(&commands, current_cmd); // son komutu da ekle
	return (commands);
}

int	validate_syntax(t_token	*tokens)
{
	
}