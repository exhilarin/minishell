/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 04:04:56 by iguney            #+#    #+#             */
/*   Updated: 2025/08/26 16:40:41 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_string(t_shell *shell, char *str)
{
	char	*result;
	char	*expanded_part;
	char	*str_ptr;

	if (str && str[0] == '\001')
		return (ft_strdup(str + 1));
	result = ft_strdup("");
	str_ptr = str;
	while (*str_ptr)
	{
		if (*str_ptr == '$')
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

static char	**filter_empty_args(char **argv)
{
	char	**new_argv;
	int		i;
	int		j;
	int		count;

	i = 0;
	count = 0;
	while (argv[i])
	{
		if (argv[i][0] != '\0')
			count++;
		i++;
	}
	new_argv = malloc(sizeof(char *) * (count + 1));
	if (!new_argv)
		return (NULL);
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
	free(argv);
	return (new_argv);
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
	int		start;
	char	*var_name;
	char	*value;

	(void)str;
	(*ptr_i)++;
	if (**ptr_i == '?')
	{
		(*ptr_i)++;
		return (ft_itoa(exit_status_manager(0, 0)));
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

char	*handle_single_quotes(char **str_ptr)
{
	char	*result;
	char	*start;
	int		len;

	(*str_ptr)++;
	start = *str_ptr;
	len = 0;
	while (**str_ptr && **str_ptr != '\'')
	{
		len++;
		(*str_ptr)++;
	}
	if (**str_ptr == '\'')
		(*str_ptr)++;
	result = ft_substr(start, 0, len);
	return (result);
}

char	*handle_double_quotes(t_shell *shell, char **str_ptr)
{
	char	*result;
	char	*expanded_part;

	result = ft_strdup("");
	(*str_ptr)++;
	while (**str_ptr && **str_ptr != '"')
	{
		if (**str_ptr == '$')
			expanded_part = expand_var(shell, *str_ptr, str_ptr);
		else
		{
			expanded_part = ft_substr(*str_ptr, 0, 1);
			(*str_ptr)++;
		}
		if (!expanded_part)
			return (free(result), NULL);
		result = join_and_free(result, expanded_part);
	}
	if (**str_ptr == '"')
		(*str_ptr)++;
	return (result);
}
