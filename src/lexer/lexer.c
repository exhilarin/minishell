/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:42:55 by ilyas-guney       #+#    #+#             */
/*   Updated: 2025/07/01 00:15:11 by ilyas-guney      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *lexer(char *input)
{
	t_token	*tokens;
	
	tokens = NULL;
	while (*input)
	{
		skip_whitespace(&input);
		if (*input == '|')
		{
			add_token(&tokens, PIPE, ft_strdup("|"), 0);
			input++;
		}
		else if (*input == '$')
			add_token(&tokens, VAR, extract_var(&input), 0);
		else if (*input == '>' || *input == '<')
			handle_redirection(&tokens, &input);
		else if (*input == '\'')
			add_token(&tokens, QUOTE_SINGLE,
				extract_single_quoted_string(&input), 1);
		else if (*input == '"')
			extract_double_quoted_string(&tokens, &input);
		else
			add_token(&tokens, WORD, extract_word(&input), 0);
	}	
	return (tokens);
}

void	add_token(t_token **tokens, t_token_type type, char *value, int quoted)
{
	t_token *new_token;
	t_token *current;

	if (!ft_strlen(value))
		return ;
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (free(value));

	new_token->type = type;
	new_token->value = value;
	new_token->quoted = quoted;
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

void	handle_redirection(t_token **tokens, char **input)
{
	if (**input == '>' && *(*input + 1) == '>')
	{
		add_token(tokens, APPEND, ft_strdup(">>"), 0);
		*input += 2;
	}
	else if (**input == '>')
	{
		add_token(tokens, REDIR_OUT, ft_strdup(">"), 0);
		(*input)++;
	}
	else if (**input == '<' && *(*input + 1) == '<')
	{
		add_token(tokens, HEREDOC, ft_strdup("<<"), 0);
		*input += 2;
	}
	else if (**input == '<')
	{
		add_token(tokens, REDIR_IN, ft_strdup("<"), 0);
		(*input)++;
	}
}
