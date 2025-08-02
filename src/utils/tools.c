/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 19:49:15 by ilyas-guney       #+#    #+#             */
/*   Updated: 2025/08/03 00:52:36 by ilyas-guney      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*init_cmd(void)
{
	t_cmd *cmd = malloc(sizeof(t_cmd));
	cmd->argv = NULL;
	cmd->redir = NULL;
	cmd->next = NULL;
	return (cmd);
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' ||
			c == '\v' || c == '\f' || c == '\r');
}

void	skip_whitespace(char **input)
{
	while (**input && ft_isspace(**input))
		(*input)++;
}

int ft_strncmp(char *s1, char *s2, int n)
{
	int i = 0;
	while (i < n)
	{
		if (s1[i] == '\0' || s2[i] == '\0' || s1[i] != s2[i])
			return 0;
		i++;
	}
	return 1;
}
