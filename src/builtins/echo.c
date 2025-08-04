/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 01:15:50 by ilyas-guney       #+#    #+#             */
/*   Updated: 2025/08/04 07:07:34 by iguney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_echo(char **args)
{
	int	i;
	int	j;
	int	newline;

	i = 0;
	newline = 1;
	while (args[++i] && ft_strncmp(args[1], "-n", 2))
	{
		j = 2;
		while (args[i][j] == 'n')
			j++;
		if (args[i][j] != '\0')
			break ;
		newline = 0;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}
