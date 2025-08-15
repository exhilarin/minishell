/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:13:23 by ilyas-guney       #+#    #+#             */
/*   Updated: 2025/08/15 06:48:11 by iguney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*parser(t_token *tokens)
{
	t_cmd	*commands;
	t_cmd	*current_cmd;
	t_token	*current_token;

	commands = NULL;
	current_cmd = init_cmd();
	if (!current_cmd)
		return (NULL);
	current_token = tokens;
	while (current_token)
	{
		if (!process_token(&current_token, &current_cmd, &commands))
			return (NULL);
		current_token = current_token->next;
	}
	add_cmd_to_lst(&commands, current_cmd);
	return (commands);
}

int	process_token(t_token **c_tkn, t_cmd **c_cmd, t_cmd **cmds)
{
	if ((*c_tkn)->type == WORD)
		add_arg_to_cmd(*c_cmd, (*c_tkn)->value);
	else if ((*c_tkn)->type == REDIR_IN || (*c_tkn)->type == REDIR_OUT
		|| (*c_tkn)->type == APPEND || (*c_tkn)->type == HEREDOC)
	{
		add_redir_to_cmd(*c_cmd, (*c_tkn)->type, (*c_tkn)->next->value);
		*c_tkn = (*c_tkn)->next;
	}
	else if ((*c_tkn)->type == PIPE)
	{
		add_cmd_to_lst(cmds, *c_cmd);
		*c_cmd = init_cmd();
		if (!(*c_cmd))
			return (0);
	}
	return (1);
}

void	add_arg_to_cmd(t_cmd *current_cmd, char *token_value)
{
	int		i;
	int		argc;
	char	**new_argv;

	argc = 0;
	if (!current_cmd || !token_value)
		return ;
	if (!token_value)
		return ;
	if (current_cmd->argv)
		while (current_cmd->argv[argc])
			argc++;
	new_argv = malloc(sizeof(char *) * (argc + 2));
	if (!new_argv)
		return ;
	i = -1;
	while (++i < argc)
		new_argv[i] = current_cmd->argv[i];
	new_argv[argc] = ft_strdup(token_value);
	if (!new_argv[argc])
		return (free(new_argv));
	new_argv[argc + 1] = NULL;
	if (current_cmd->argv)
		free(current_cmd->argv);
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
