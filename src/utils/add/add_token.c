/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 20:25:01 by iguney            #+#    #+#             */
/*   Updated: 2025/08/27 23:07:58 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_token(t_token **tokens, t_token_type type, char *value)
{
	t_token	*new_token;
	t_token	*current;

	if (!ft_strlen(value))
	{
		free(value);
		return ;
	}
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (free_tokens(*tokens), free(value));
	new_token->type = type;
	new_token->value = value;
	new_token->quoted = 0;
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

void	add_token_with_quote(t_token **tokens, t_token_type type,
		char *value, int quote_type)
{
	t_token	*new_token;
	t_token	*current;

	if (!ft_strlen(value))
	{
		free(value);
		return ;
	}
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (free_tokens(*tokens), free(value));
	new_token->type = type;
	new_token->value = value;
	new_token->quoted = quote_type;
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

char	*add_quote_marker(char *result, char quote, char **input)
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

char	*add_end_marker(char *result, char **input)
{
	char	*tmp;
	char	*marker;

	marker = "\003";
	tmp = ft_strjoin(result, marker);
	free(result);
	(*input)++;
	return (tmp);
}
