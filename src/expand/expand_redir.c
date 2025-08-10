/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 14:06:18 by iguney            #+#    #+#             */
/*   Updated: 2025/08/10 22:57:17 by iguney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_single_quoted(char *arg)
{
	int	i;
	int	len;
	int	count;

	i = -1;
	count = 0;
	len = ft_strlen(arg);
	while (arg[++i])
	{
		if (arg[i] == '\'')
			count++;
	}
	if (len >= 2 && count == 2
		&& arg[0] == '\'' && arg[len - 1] == '\'')
		return (1);
	return (0);
}

char	*remove_single_quotes(char *arg)
{
	int start;
	int end;

	start = 1;
	end = ft_strlen(arg) - 2;
	return(ft_substr(arg, start, end));
}