/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 21:52:25 by iguney            #+#    #+#             */
/*   Updated: 2025/08/27 22:03:34 by iguney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_single_quotes(char **str_ptr)
{
	char	*result;
	char	*start;
	int		len;

	(*str_ptr)++;
	start = *str_ptr;
	len = 0;
	while (**str_ptr && **str_ptr != '\'')
	{
		len++;
		(*str_ptr)++;
	}
	if (**str_ptr == '\'')
		(*str_ptr)++;
	result = ft_substr(start, 0, len);
	return (result);
}

char	*handle_double_quotes(t_shell *shell, char **str_ptr)
{
	char	*result;
	char	*expanded_part;

	result = ft_strdup("");
	(*str_ptr)++;
	while (**str_ptr && **str_ptr != '"')
	{
		if (**str_ptr == '$')
			expanded_part = expand_var(shell, *str_ptr, str_ptr);
		else
		{
			expanded_part = ft_substr(*str_ptr, 0, 1);
			(*str_ptr)++;
		}
		if (!expanded_part)
			return (free(result), NULL);
		result = join_and_free(result, expanded_part);
	}
	if (**str_ptr == '"')
		(*str_ptr)++;
	return (result);
}

void	handle_quote_chars(char **str_ptr, int *in_single_quotes)
{
	if (**str_ptr == '\001')
	{
		*in_single_quotes = 1;
		(*str_ptr)++;
	}
	else if (**str_ptr == '\002')
	{
		*in_single_quotes = 0;
		(*str_ptr)++;
	}
	else if (**str_ptr == '\003')
	{
		*in_single_quotes = 0;
		(*str_ptr)++;
	}
}

char	*handle_regular_char(t_shell *shell, char *str, char **str_ptr,
			int in_single_quotes)
{
	char	*expanded_part;

	if (**str_ptr == '$' && !in_single_quotes)
		expanded_part = expand_var(shell, str, str_ptr);
	else
	{
		expanded_part = ft_substr(*str_ptr, 0, 1);
		(*str_ptr)++;
	}
	return (expanded_part);
}

char	*handle_special_vars(char **ptr_i)
{
	if (**ptr_i == '?')
	{
		(*ptr_i)++;
		return (ft_itoa(exit_status_manager(0, 0)));
	}
	if (**ptr_i == '$')
	{
		(*ptr_i)++;
		return (ft_strdup(""));
	}
	return (NULL);
}
