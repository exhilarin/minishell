/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 19:49:15 by ilyas-guney       #+#    #+#             */
/*   Updated: 2025/08/10 16:58:31 by iguney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->argv = NULL;
	cmd->redir = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_exec	*init_exec()
{
	t_exec *exec;

	exec = malloc(sizeof(t_exec));
	exec->cmd_path = NULL;
	exec->paths = NULL;
	exec->envp = NULL;
	return(exec);
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

void	skip_whitespace(char **input)
{
	while (**input && ft_isspace(**input))
		(*input)++;
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