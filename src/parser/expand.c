/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 04:04:56 by iguney            #+#    #+#             */
/*   Updated: 2025/08/25 04:34:39 by iguney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_string(t_shell *shell, char *str)
{
	char	*result;
	char	*expanded_part;
	char	*str_ptr;

	result = ft_strdup("");
	str_ptr = str;
	while (*str_ptr)
	{
		if (*str_ptr == '\'' || *str_ptr == '"')
			expanded_part = handle_quoted_part(&str_ptr, *str_ptr);
		else if (*str_ptr == '$')
			expanded_part = expand_var(shell, str, &str_ptr);
		else
		{
			expanded_part = ft_substr(str_ptr, 0, 1);
			str_ptr++;
		}
		if (!expanded_part)
			return (free(result), NULL);
		result = join_and_free(result, expanded_part);
	}
	return (result);
}

void	expand_all(t_shell *shell)
{
	t_cmd	*cmd;

	cmd = shell->command_list;
	while (cmd)
	{
		expand_args(shell, cmd);
		expand_redirs(shell, cmd);
		cmd = cmd->next;
	}
}

void	expand_args(t_shell *shell, t_cmd *cmd)
{
	int		i;
	char	*expanded;

	if (!cmd->argv)
		return ;
	i = 0;
	while (cmd->argv[i])
	{
		expanded = expand_string(shell, cmd->argv[i]);
		free(cmd->argv[i]);
		cmd->argv[i] = expanded;
		i++;
	}
}

void	expand_redirs(t_shell *shell, t_cmd *cmd)
{
	t_redir	*redir;
	char	*expanded;

	redir = cmd->redir;
	while (redir)
	{
		expanded = expand_string(shell, redir->file);
		free(redir->file);
		redir->file = expanded;
		redir = redir->next;
	}
}

char	*expand_var(t_shell *shell, char *str, char **ptr_i)
{
	int		start;
	char	*var_name;
	char	*value;

	(void)str;
	(*ptr_i)++;
	if (**ptr_i == '?')
	{
		(*ptr_i)++;
		return (ft_itoa(shell->exit_status));
	}
	if (!ft_isalpha(**ptr_i) && **ptr_i != '_')
		return (ft_strdup("$"));
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
