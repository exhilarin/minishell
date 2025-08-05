/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 19:51:17 by ilyas-guney       #+#    #+#             */
/*   Updated: 2025/08/05 03:56:57 by iguney           ###   ########.fr       */
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
		perror("syntax error: invalid character\n");
	if (err_code == ERR_PIPE_START)
		perror("syntax error: unexpected pipe at start\n");
	else if (err_code == ERR_PIPE_DOUBLE)
		perror("syntax error: double pipe `||`\n");
	else if (err_code == ERR_REDIR_EOF)
		perror("syntax error: redirection without target\n");
	else if (err_code == ERR_PIPE_EOF)
		perror("syntax error: unexpected token\n");
}

int	shutdown_shell(t_shell *shell)
{
	if (!shell)
		return (shell->exit_status);
	if (shell->token_list)
		free_tokens(shell->token_list);
	if (shell->command_list)
		free_cmd(shell->command_list);
	if (shell->input)
		free(shell->input);
	rl_clear_history();
	return (shell->exit_status);
}
