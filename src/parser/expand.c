/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 06:38:03 by iguney            #+#    #+#             */
/*   Updated: 2025/08/18 23:54:06 by ilyas-guney      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		expanded = expand_string(shell, cmd->argv[i], 0);
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
		expanded = expand_string(shell, redir->file, 0);
		free(redir->file);
		redir->file = expanded;
		redir = redir->next;
	}
}

char	*expand_string(t_shell *shell, char *str, int quote)
{
	char	*result;
	int		i;
	char	*substr;

	result = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && quote == 0)
			quote = str[i++];
		else if (str[i] == quote)
			quote = 0, i++;
		else if (str[i] == '$' && quote != '\'')
			result = join_and_free(result, expand_var(shell, str, &i));
		else
		{
			substr = ft_substr(str, i, 1);
			result = join_and_free(result, substr);
			i++;
		}
	}
	return (result);
}

char	*expand_var(t_shell *shell, char *str, int *i)
{
	int		start;
	char	*var_name;
	char	*value;

	(*i)++;
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(shell->exit_status));
	}
	if (!ft_isalpha(str[*i]) && str[*i] != '_')
		return (ft_strdup("$"));
	start = *i;
	while (ft_isalnum(str[*i]) || str[*i] == '_')
		(*i)++;
	var_name = ft_substr(str, start, *i - start);
	value = get_env_value(shell->env, var_name);
	free(var_name);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}
