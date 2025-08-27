/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 01:15:50 by ilyas-guney       #+#    #+#             */
/*   Updated: 2025/08/27 19:18:40 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_echo_flags(char **args, int *newline)
{
	int	i;
	int	j;

	i = 1;
	*newline = 1;
	while (args[i] && args[i][0] == '-' && args[i][1] == 'n')
	{
		j = 2;
		while (args[i][j] == 'n')
			j++;
		if (args[i][j] != '\0')
			break ;
		*newline = 0;
		i++;
	}
	return (i);
}

static void	print_echo_args(char **args, int start_index)
{
	int	i;

	i = start_index;
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
}

void	builtin_echo(char **args)
{
	int	newline;
	int	start_index;

	start_index = parse_echo_flags(args, &newline);
	print_echo_args(args, start_index);
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	exit_status_manager(0, 1);
}
