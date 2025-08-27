/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 21:55:39 by iguney            #+#    #+#             */
/*   Updated: 2025/08/27 22:05:21 by iguney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_var_name(t_shell *shell, char **ptr_i)
{
	int		start;
	char	*var_name;
	char	*value;

	start = 0;
	while (ft_isalnum((*ptr_i)[start]) || (*ptr_i)[start] == '_')
		start++;
	var_name = ft_substr(*ptr_i, 0, start);
	value = get_env_value(shell->env, var_name);
	free(var_name);
	*ptr_i += start;
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

int	count_non_empty_args(char **argv)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (argv[i])
	{
		if (argv[i][0] != '\0')
			count++;
		i++;
	}
	return (count);
}

void	copy_non_empty_args(char **argv, char **new_argv)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (argv[i])
	{
		if (argv[i][0] != '\0')
			new_argv[j++] = argv[i];
		else
			free(argv[i]);
		i++;
	}
	new_argv[j] = NULL;
}

char	**filter_empty_args(char **argv)
{
	char	**new_argv;
	int		count;

	count = count_non_empty_args(argv);
	new_argv = malloc(sizeof(char *) * (count + 1));
	if (!new_argv)
		return (NULL);
	copy_non_empty_args(argv, new_argv);
	free(argv);
	return (new_argv);
}

int	is_simple_single_quote(char *str)
{
	if (!str)
		return (0);
	if (str[0] != '\001')
		return (0);
	if (ft_strchr(str, '\002'))
		return (0);
	if (ft_strchr(str, '\003'))
		return (0);
	return (1);
}
