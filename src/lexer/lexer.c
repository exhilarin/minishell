/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 04:20:36 by iguney            #+#    #+#             */
/*   Updated: 2025/08/25 04:20:37 by iguney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*lexer(char *input)
{
	t_token	*tokens;

	tokens = NULL;
	while (*input)
	{
		skip_whitespace(&input);
		if (*input == '|')
		{
			add_token(&tokens, PIPE, ft_strdup("|"));
			input++;
		}
		else if (*input == '>' || *input == '<')
			handle_redirection(&tokens, &input);
		else if (!handle_word_token(&tokens, &input))
			return (NULL);
	}
	return (tokens);
}

void	handle_redirection(t_token **tokens, char **input)
{
	if (**input == '>' && *(*input + 1) == '>')
	{
		add_token(tokens, APPEND, ft_strdup(">>"));
		*input += 2;
	}
	else if (**input == '>')
	{
		add_token(tokens, REDIR_OUT, ft_strdup(">"));
		(*input)++;
	}
	else if (**input == '<' && *(*input + 1) == '<')
	{
		add_token(tokens, HEREDOC, ft_strdup("<<"));
		*input += 2;
	}
	else if (**input == '<')
	{
		add_token(tokens, REDIR_IN, ft_strdup("<"));
		(*input)++;
	}
}

int	handle_word_token(t_token **tokens, char **input)
{
	char	*word;
	int		quote_type;

	quote_type = extract_word_with_quote(input, &word);
	if (!word)
	{
		free_tokens(*tokens);
		return (0);
	}
	add_token_with_quote(tokens, WORD, word, quote_type);
	return (1);
}

char	*extract_word(char **input)
{
	char	*result;
	char	*tmp;
	char	c[2];

	result = ft_strdup("");
	while (**input && !ft_isspace(**input)
		&& **input != '|' && **input != '<' && **input != '>')
	{
		if (**input == '"' || **input == '\'')
		{
			result = append_quoted_part(input, result, **input);
			if (!result)
				return (NULL);
		}
		else
		{
			c[0] = **input;
			c[1] = '\0';
			tmp = ft_strjoin(result, c);
			free(result);
			result = tmp;
			(*input)++;
		}
	}
	return (result);
}

int	extract_word_with_quote(char **input, char **word)
{
	char	*result;
	char	*tmp;
	char	c[2];
	int		quote_type;

	result = ft_strdup("");
	quote_type = 0;
	while (**input && !ft_isspace(**input)
		&& **input != '|' && **input != '<' && **input != '>')
	{
		if (**input == '"' || **input == '\'')
		{
			if (**input == '\'')
				quote_type = 1;
			result = append_quoted_part(input, result, **input);
			if (!result)
				return (0);
		}
		else
		{
			c[0] = **input;
			c[1] = '\0';
			tmp = ft_strjoin(result, c);
			free(result);
			result = tmp;
			(*input)++;
		}
	}
	*word = result;
	return (quote_type);
}
