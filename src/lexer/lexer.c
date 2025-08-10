/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:42:55 by ilyas-guney       #+#    #+#             */
/*   Updated: 2025/08/11 00:36:25 by iguney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *extract_word_with_quotes(char **input)
{
	char    *result;
	char    *tmp;
	char    c[2];

	result = ft_strdup("");
	while (**input && !ft_isspace(**input)
		&& **input != '|' && **input != '<' && **input != '>')
	{
		if (**input == '\'' || **input == '"')
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

static int	handle_word_token(t_token **tokens, char **input)
{
	char	*word;

	word = extract_word_with_quotes(input);
	if (!word)
	{
		free_tokens(*tokens);
		return (0);
	}
	add_token(tokens, WORD, word, 0);
	return (1);
}

t_token	*lexer(char *input)
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
		else if (!handle_word_token(&tokens, &input))
			return (NULL);
	}
	return (tokens);
}

void	add_token(t_token **tokens, t_token_type type, char *value, int quoted)
{
	t_token	*new_token;
	t_token	*current;

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
