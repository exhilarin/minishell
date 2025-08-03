/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 19:51:17 by ilyas-guney       #+#    #+#             */
/*   Updated: 2025/08/03 20:11:28 by iguney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_invalid_char(char *input)
{
	while (*input)
	{
		if (*input == ';' || *input == '\\')
			return (1);
		input++;
	}
	return (0);
}

int	validate_syntax(t_token *tokens)
{
	if (tokens && tokens->type == PIPE)
		return (ERR_PIPE_START);
	while (tokens && tokens->next)
	{
		if (tokens->type == PIPE && tokens->next->type == PIPE)
			return (ERR_PIPE_DOUBLE);
		else if (tokens->type == PIPE && ((tokens->next->type == REDIR_IN
					|| tokens->next->type == REDIR_OUT
					|| tokens->next->type == APPEND
					|| tokens->next->type == HEREDOC)))
			return (ERR_REDIR_EOF);
		else if ((tokens->type == REDIR_IN || tokens->type == REDIR_OUT
				|| tokens->type == APPEND || tokens->type == HEREDOC)
			&& (tokens->next == NULL || tokens->next->type == PIPE))
			return (ERR_REDIR_EOF);
		tokens = tokens->next;
	}
	if (tokens && (tokens->type == REDIR_IN || tokens->type == REDIR_OUT
			|| tokens->type == APPEND || tokens->type == HEREDOC))
		return (ERR_REDIR_EOF);
	if (tokens && tokens->type == PIPE)
		return (ERR_PIPE_EOF);
	return (SYNTAX_OK);
}

void	syntax_error(int err_code)
{
	if (err_code == ERR_INVALID)
		fprintf(stderr, "syntax error: invalid character\n");
	if (err_code == ERR_PIPE_START)
		fprintf(stderr, "syntax error: unexpected pipe at start\n");
	else if (err_code == ERR_PIPE_DOUBLE)
		fprintf(stderr, "syntax error: double pipe `||`\n");
	else if (err_code == ERR_REDIR_EOF)
		fprintf(stderr, "syntax error: redirection without target\n");
	else if (err_code == ERR_PIPE_EOF)
		fprintf(stderr, "syntax error: unexpected token\n");
}
