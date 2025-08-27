/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 19:49:15 by ilyas-guney       #+#    #+#             */
/*   Updated: 2025/08/27 19:25:14 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_and_free(char *s1, char *s2)
{
	char	*joined;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (s1);
	joined = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (joined);
}

static char	*add_quote_marker(char *result, char quote, char **input)
{
	char	*tmp;
	char	*marker;

	if (quote == '\'')
		marker = "\001";
	else
		marker = "\002";
	tmp = ft_strjoin(result, marker);
	free(result);
	(*input)++;
	return (tmp);
}

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

static char	*add_end_marker(char *result, char **input)
{
	char	*tmp;
	char	*marker;

	marker = "\003";
	tmp = ft_strjoin(result, marker);
	free(result);
	(*input)++;
	return (tmp);
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
