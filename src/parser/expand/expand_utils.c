/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 21:55:39 by iguney            #+#    #+#             */
/*   Updated: 2025/08/28 03:58:54 by iguney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_string(t_shell *shell, char *str)
{
	if ((str[0] == '\'' && str[1] == '\'' && str[2] == '\0')
		|| (str[0] == '"' && str[1] == '"' && str[2] == '\0'))
		return (ft_strdup(""));
	if (is_simple_single_quote(str))
		return (ft_strdup(str + 1));
	return (expand_string_core(shell, str, ft_strdup("")));
}

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
