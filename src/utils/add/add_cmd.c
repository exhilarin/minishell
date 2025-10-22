/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 23:03:20 by mugenan           #+#    #+#             */
/*   Updated: 2025/08/27 23:29:29 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_arg_to_cmd(t_cmd *current_cmd, char *token_value)
{
	int		argc;
	char	**new_argv;
	int		i;

	if (!current_cmd || !token_value)
		return ;
	argc = 0;
	if (current_cmd->argv)
		while (current_cmd->argv[argc])
			argc++;
	new_argv = add_argv(current_cmd->argv, token_value, argc);
	if (!new_argv)
		return ;
	if (current_cmd->argv)
	{
		i = 0;
		while (current_cmd->argv[i])
			free(current_cmd->argv[i++]);
		free(current_cmd->argv);
	}
	current_cmd->argv = new_argv;
}

void	add_redir_to_cmd(t_cmd *cmd, int type, char *file)
{
	t_redir	*tmp;
	t_redir	*new_redir;

	if (!file)
		return ;
	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return ;
	new_redir->type = type;
	new_redir->file = ft_strdup(file);
	if (!new_redir->file)
	{
		free(new_redir);
		return ;
	}
	new_redir->next = NULL;
	if (!cmd->redir)
		cmd->redir = new_redir;
	else
	{
		tmp = cmd->redir;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_redir;
	}
}

void	add_cmd_to_lst(t_cmd **cmds, t_cmd *new_cmd)
{
	t_cmd	*tmp;

	if (!cmds || !new_cmd)
		return ;
	if (!*cmds)
	{
		*cmds = new_cmd;
		return ;
	}
	tmp = *cmds;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_cmd;
}

void	free_argv(char **new_argv, int i)
{
	while (--i >= 0)
		free(new_argv[i]);
	free(new_argv);
}

char	**add_argv(char **old_argv, char *token_value, int argc)
{
	char	**new_argv;
	int		i;

	new_argv = malloc(sizeof(char *) * (argc + 2));
	if (!new_argv)
		return (NULL);
	i = -1;
	while (++i < argc)
	{
		new_argv[i] = ft_strdup(old_argv[i]);
		if (!new_argv[i])
		{
			free_argv(new_argv, i);
			return (NULL);
		}
	}
	new_argv[argc] = ft_strdup(token_value);
	if (!new_argv[argc])
	{
		free_argv(new_argv, i);
		return (NULL);
	}
	new_argv[argc + 1] = NULL;
	return (new_argv);
}
