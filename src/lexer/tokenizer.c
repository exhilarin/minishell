/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 22:09:35 by iguney            #+#    #+#             */
/*   Updated: 2025/08/27 22:30:57 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_quote_char(char **input, char **result, int *quote_type)
{
	if (**input == '\'')
		*quote_type = 1;
	*result = append_quoted_part(input, *result, **input);
	if (!*result)
		return (0);
	return (1);
}

int	handle_char(char **input, char **result)
{
	char	*tmp;
	char	c[2];

	c[0] = **input;
	c[1] = '\0';
	tmp = ft_strjoin(*result, c);
	free(*result);
	*result = tmp;
	if (!tmp)
		return (0);
	(*input)++;
	return (1);
}

int	process_word_chars(char **input, char **result, int *quote_type)
{
	while (**input && !ft_isspace(**input)
		&& **input != '|' && **input != '<' && **input != '>')
	{
		if (**input == '"' || **input == '\'')
		{
			if (!handle_quote_char(input, result, quote_type))
				return (0);
		}
		else
		{
			if (!handle_char(input, result))
				return (0);
		}
	}
	return (1);
}

int	init_word_extraction(char **result, char **word)
{
	*result = ft_strdup("");
	if (!*result)
	{
		*word = NULL;
		return (0);
	}
	return (1);
}
