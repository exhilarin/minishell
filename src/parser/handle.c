/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 04:04:56 by iguney            #+#    #+#             */
/*   Updated: 2025/08/25 05:13:51 by iguney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_quoted_part(char **str, char quote)
{
	char	*result;
	int		len;
	int		i;

	i = 0;
	len = 0;
	if (**str == quote)
	{
		i++;
		len++;
	}
	while ((*str)[i] && (*str)[i] != quote)
	{
		i++;
		len++;
	}
	if ((*str)[i] == quote)
	{
		i++;
		len++;
	}
	result = ft_substr(*str, 0, len);
	*str += len;
	return (result);
}

char	*handle_quote(char **str, int *quote)
{
	int		start;
	char	*result;

	(*str)++;
	start = 0;
	while ((*str)[start] && (*str)[start] != *quote)
		start++;
	result = ft_substr(*str, 0, start);
	*str += start;
	if (**str == *quote)
		(*str)++;
	*quote = 0;
	return (result);
}

char	*handle_char(char *str, int *i)
{
	char	*substr;

	substr = ft_substr(str, *i, 1);
	(*i)++;
	return (substr);
}
