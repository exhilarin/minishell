/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 04:04:56 by iguney            #+#    #+#             */
/*   Updated: 2025/08/27 22:02:53 by iguney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_string(t_shell *shell, char *str)
{
	char	*result;
	char	*expanded_part;
	char	*str_ptr;
	int		in_single_quotes;

	if (is_simple_single_quote(str))
		return (ft_strdup(str + 1));
	result = ft_strdup("");
	str_ptr = str;
	in_single_quotes = 0;
	while (*str_ptr)
	{
		if (*str_ptr == '\001' || *str_ptr == '\002' || *str_ptr == '\003')
			handle_quote_chars(&str_ptr, &in_single_quotes);
		else
		{
			expanded_part = handle_regular_char(shell, str, &str_ptr,
					in_single_quotes);
			if (!expanded_part)
				return (free(result), NULL);
			result = join_and_free(result, expanded_part);
		}
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
		// Export builtin için özel expansion mantığı
		if (i == 0 || !cmd->argv[0] || ft_strcmp(cmd->argv[0], "export") != 0)
		{
			expanded = expand_string(shell, cmd->argv[i]);
			free(cmd->argv[i]);
			cmd->argv[i] = expanded;
		}
		else
		{
			// Export argümanları için sadece assignment içeren argümanları expand et
			if (ft_strchr(cmd->argv[i], '='))
			{
				expanded = expand_string(shell, cmd->argv[i]);
				free(cmd->argv[i]);
				cmd->argv[i] = expanded;
			}
			// '=' içermeyenler expand edilmez (değişken adları olarak kalır)
		}
		i++;
	}
	cmd->argv = filter_empty_args(cmd->argv);
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
	char	*result;

	(void)str;
	(*ptr_i)++;
	result = handle_special_vars(ptr_i);
	if (result)
		return (result);
	if (!ft_isalpha(**ptr_i) && **ptr_i != '_')
		return (ft_strdup("$"));
	return (extract_var_name(shell, ptr_i));
}
