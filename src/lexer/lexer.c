/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:42:55 by ilyas-guney       #+#    #+#             */
/*   Updated: 2025/06/28 02:18:35 by ilyas-guney      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *lexer(char *input)
{
	t_token	*tokens = NULL;

	while (*input)
	{
		skip_whitespace(&input);
		if (*input == '|')
		{
			add_token(&tokens, PIPE, ft_strdup("|"), 0);
			input++;
		}
		else if (*input == '>' || *input == '<')
			handle_redirection(&tokens, &input);
		else if (*input == '\'')
			add_token(&tokens, QUOTE_SINGLE,
				extract_quoted_string(&input), 1);
		else if (*input == '"')
			add_token(&tokens, QUOTE_DOUBLE,
				extract_quoted_string(&input), 2);
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
		exit(1);

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

char	*extract_quoted_string(char **input)
{
	char	*start;
	int 	length;
	char	*result;
	char	quote_char;
	
	quote_char = **input;
	(*input)++;
	start = *input;
	while (**input && **input != quote_char)
		(*input)++;
	length = *input - start; 
	if (**input == quote_char)
		(*input)++;
	result = malloc(length + 1);
	if (!result)
		exit(1);
	ft_strlcpy(result, start, length + 1);
	result[length] = '\0';
	return (result);
}

char	*extract_word(char **input)
{
	char	*start;
	int		length;
	char	*result;

	start = *input;
	while (**input && 
		!ft_isspace(**input) &&
		**input != '|' &&
		**input != '<' &&
		**input != '>' &&
		**input != '\'' &&
		**input != '"')
		(*input)++;
	length = *input - start;
	result = malloc(length + 1);
	if (!result)
		exit(1);
	ft_strlcpy(result, start, length + 1);
	result[length] = '\0';
	return (result);
}
