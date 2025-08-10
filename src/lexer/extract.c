/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 00:14:18 by ilyas-guney       #+#    #+#             */
/*   Updated: 2025/08/11 00:37:12 by iguney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_var(char **input)
{
	char	*start;
	int		len;

	if (**input != '$')
		return (NULL);
	(*input)++;
	if (**input == '?')
	{
		(*input)++;
		return (ft_strdup("?"));
	}
	start = *input;
	len = 0;
	while ((*input)[len] && (ft_isalnum((*input)[len]) || (*input)[len] == '_'))
		len++;
	*input += len;
	return (ft_substr(start, 0, len));
}

char	*extract_single_quoted_string(char **input)
{
	char	*start;
	int		length;

	if (**input != '\'')
		return (NULL);
	(*input)++;
	start = *input;
	while (**input && **input != '\'')
		(*input)++;
	length = *input - start;
	if (**input == '\'')
		(*input)++;
	return (ft_substr(start, 0, length));
}

void	extract_double_quoted_string(t_token **tokens, char **input)
{
	char	*start;
	int		length;

	if (**input != '"')
		return ;
	(*input)++;
	start = *input;
	while (**input && **input != '"')
	{
		if (**input == '$')
		{
			length = *input - start;
			if (length > 0)
				add_token(tokens, QUOTE_DOUBLE, ft_substr(start, 0, length), 2);
			add_token(tokens, VAR, extract_var(input), 2);
			start = *input;
		}
		else
			(*input)++;
	}
	length = *input - start;
	if (length > 0)
		add_token(tokens, QUOTE_DOUBLE, ft_substr(start, 0, length), 2);
	if (**input == '"')
		(*input)++;
}

char	*extract_word(char **input)
{
	char	*start;
	int		length;

	start = *input;
	while (**input
		&& !ft_isspace(**input)
		&& **input != '|'
		&& **input != '<'
		&& **input != '>'
		&& **input != '\''
		&& **input != '"')
		(*input)++;
	length = *input - start;
	return (ft_substr(start, 0, length));
}

char *append_quoted_part(char **input, char *result, char quote)
{
	char	*tmp;
	char	*part;
	char	*start;

	(*input)++;
	start = *input;
	while (**input && **input != quote)
		(*input)++;
	if (**input == '\0')
		return (free(result), NULL);
	part = ft_substr(start, 0, *input - start);
	tmp = ft_strjoin(result, part);
	free(result);
	free(part);
	(*input)++;
	return (tmp);
}