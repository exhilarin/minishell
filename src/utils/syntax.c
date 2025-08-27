/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 19:51:17 by ilyas-guney       #+#    #+#             */
/*   Updated: 2025/08/26 17:07:30 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_invalid_char(char *input)
{
	int		in_quote;
	char	quote_char;

	in_quote = 0;
	quote_char = 0;
	while (*input)
	{
		if ((*input == '"' || *input == '\'') && !in_quote)
		{
			in_quote = 1;
			quote_char = *input;
		}
		else if (*input == quote_char && in_quote)
		{
			in_quote = 0;
			quote_char = 0;
		}
		else if (!in_quote && (*input == ';' || *input == '\\'))
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
	if ((tokens->type == REDIR_IN || tokens->type == REDIR_OUT
			|| tokens->type == APPEND || tokens->type == HEREDOC)
		&& (tokens->next == NULL || tokens->next->type == PIPE))
		return (ERR_REDIR_EOF);
	return (SYNTAX_OK);
}

void	syntax_error(int err_code)
{
	if (err_code == ERR_INVALID)
		print_error("syntax error: unexpected token\n", 2);
	if (err_code == ERR_PIPE_START)
		print_error("syntax error: unexpected pipe at start\n", 2);
	else if (err_code == ERR_PIPE_DOUBLE)
		print_error("syntax error: double pipe `||`\n", 2);
	else if (err_code == ERR_REDIR_EOF)
		print_error("syntax error: redirection without target\n", 2);
	else if (err_code == ERR_PIPE_EOF)
		print_error("syntax error: unexpected token\n", 2);
	else if (err_code == ERR_UNCLOSED_QUOTES)
		print_error("syntax error: unclosed quote\n", 2);
}
