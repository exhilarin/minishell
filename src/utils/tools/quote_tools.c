/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 04:07:41 by iguney            #+#    #+#             */
/*   Updated: 2025/08/28 04:07:43 by iguney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*process_quote_content(char *result, char **input, char quote)
{
	char	*tmp;
	char	c[2];

	c[1] = '\0';
	while (**input && **input != quote)
	{
		c[0] = **input;
		tmp = ft_strjoin(result, c);
		free(result);
		result = tmp;
		(*input)++;
	}
	return (result);
}

char	*append_quoted_part(char **input, char *result, char quote)
{
	result = add_quote_marker(result, quote, input);
	result = process_quote_content(result, input, quote);
	if (**input != quote)
		return (free(result), NULL);
	return (add_end_marker(result, input));
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

void	skip_whitespace(char **input)
{
	while (**input && ft_isspace(**input))
		(*input)++;
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}
