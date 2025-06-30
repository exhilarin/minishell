/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 19:51:17 by ilyas-guney       #+#    #+#             */
/*   Updated: 2025/06/30 21:36:56 by ilyas-guney      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	validate_syntax(t_token *tokens)
{
	if (tokens && tokens->type == PIPE)
		return (ERR_PIPE_START);
	while (tokens && tokens->next)
	{
		if (tokens->type == PIPE && tokens->next->type == PIPE)
			return (ERR_PIPE_DOUBLE);
		else if ((tokens->type == REDIR_IN || tokens->type == REDIR_OUT
			|| tokens->type == APPEND || tokens->type == HEREDOC)
			&& (tokens->next == NULL || tokens->next->type == PIPE))
			return (ERR_REDIR_EOF);
		tokens = tokens->next;
	}
	if (tokens && (tokens->type == REDIR_IN || tokens->type == REDIR_OUT
		|| tokens->type == APPEND || tokens->type == HEREDOC))
		return (ERR_REDIR_EOF);
	return (SYNTAX_OK);
}

void	syntax_error(int err_code)
{
	if (err_code == ERR_PIPE_START)
		fprintf(stderr, "syntax error: unexpected pipe at start\n");
	else if (err_code == ERR_PIPE_DOUBLE)
		fprintf(stderr, "syntax error: double pipe `||`\n");
	else if (err_code == ERR_REDIR_EOF)
		fprintf(stderr, "syntax error: redirection without target\n");
}


void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		if (tokens->value)
			free(tokens->value);
		free (tokens);
		tokens = tmp;
	}
}

void	free_cmd(t_cmd  *commands)
{
	t_cmd	*tmp;

	while (commands)
	{
		tmp = commands->next;
		if (commands->argv)
			free(commands->argv);
		free(commands);
		commands = tmp;
	}
}
