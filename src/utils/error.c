/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 19:51:17 by ilyas-guney       #+#    #+#             */
/*   Updated: 2025/08/11 00:48:06 by iguney           ###   ########.fr       */
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
		printf("syntax error: invalid character\n");
	if (err_code == ERR_PIPE_START)
		printf("syntax error: unexpected pipe at start\n");
	else if (err_code == ERR_PIPE_DOUBLE)
		printf("syntax error: double pipe `||`\n");
	else if (err_code == ERR_REDIR_EOF)
		printf("syntax error: redirection without target\n");
	else if (err_code == ERR_PIPE_EOF)
		printf("syntax error: unexpected token\n");
}

int	shutdown_shell(t_shell *shell)
{
	int	status;

	if (!shell)
		return (1);
	status = shell->exit_status;
	free_all(shell);
	if (shell->env)
	{
		free_env(shell->env);
		shell->env = NULL;
	}
	rl_clear_history();
	shell = NULL;
	return (status);
}
