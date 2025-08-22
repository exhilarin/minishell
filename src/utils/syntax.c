/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 19:51:17 by ilyas-guney       #+#    #+#             */
/*   Updated: 2025/08/23 00:28:50 by ilyas-guney      ###   ########.fr       */
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

int	is_unclosed_quotes(const char *input)
{
	char	quote;
	int		i;

	quote = 0;
	i = 0;
	while (input[i])
	{
		if ((input[i] == '"' || input[i] == '\'') && quote == 0)
			quote = input[i];
		else if (input[i] == quote)
			quote = 0;
		i++;
	}
	return (quote != 0);
}

int	validate_syntax(t_shell *shell, t_token *tokens)
{
	if (is_invalid_char(shell->input))
		return (ERR_INVALID);
	if (is_unclosed_quotes(shell->input))
		return (ERR_UNCLOSED_QUOTES);
	if (tokens && tokens->type == PIPE)
		return (ERR_PIPE_START);
	while (tokens && tokens->next)
	{
		if (validate_redir(tokens) != SYNTAX_OK)
			return (ERR_REDIR_EOF);
		if (tokens->type == PIPE && tokens->next->type == PIPE)
			return (ERR_PIPE_DOUBLE);
		tokens = tokens->next;
	}
	if (tokens && (tokens->type == REDIR_IN || tokens->type == REDIR_OUT
			|| tokens->type == APPEND || tokens->type == HEREDOC))
		return (ERR_REDIR_EOF);
	if (tokens && tokens->type == PIPE)
		return (ERR_PIPE_EOF);
	return (SYNTAX_OK);
}

int	validate_redir(t_token *tokens)
{
	if (tokens->type == PIPE && ((tokens->next->type == REDIR_IN
				|| tokens->next->type == REDIR_OUT
				|| tokens->next->type == APPEND
				|| tokens->next->type == HEREDOC)))
		return (ERR_REDIR_EOF);
	else if ((tokens->type == REDIR_IN || tokens->type == REDIR_OUT
			|| tokens->type == APPEND || tokens->type == HEREDOC)
		&& (tokens->next == NULL || tokens->next->type == PIPE))
		return (ERR_REDIR_EOF);
	return (SYNTAX_OK);
}

void	syntax_error(t_shell *shell, int err_code)
{
	if (err_code == ERR_INVALID)
		print_error("syntax error: unexpected token\n", shell, 2);
	if (err_code == ERR_PIPE_START)
		print_error("syntax error: unexpected pipe at start\n", shell, 2);
	else if (err_code == ERR_PIPE_DOUBLE)
		print_error("syntax error: double pipe `||`\n", shell, 2);
	else if (err_code == ERR_REDIR_EOF)
		print_error("syntax error: redirection without target\n", shell, 2);
	else if (err_code == ERR_PIPE_EOF)
		print_error("syntax error: unexpected token\n", shell, 2);
	else if (err_code == ERR_UNCLOSED_QUOTES)
		print_error("syntax error: unclosed quote\n", shell, 2);
}
