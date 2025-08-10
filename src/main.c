/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:53:57 by mugenan           #+#    #+#             */
/*   Updated: 2025/08/10 23:15:02 by iguney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *env[])
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	init_shell(&shell);
	init_env(&shell, env);
	while (1)
	{
		shell.input = prompt();
		if (!shell.input)
		{
			printf("exit\n");
			return (shutdown_shell(&shell));
		}
		if (*shell.input)
			add_history(shell.input);
		process(&shell);
	}
}

void	init_shell(t_shell *shell)
{
	shell->exit_status = 0;
	shell->token_list = NULL;
	shell->command_list = NULL;
	shell->env = NULL;
	shell->exec = NULL;
}

void	process(t_shell *shell)
{
	int		syntax_err;

	if (is_invalid_char(shell->input))
	{
		syntax_error(ERR_INVALID);
		shell->exit_status = 1;
		free_all(shell);
		return ;
	}
	shell->token_list = lexer(shell->input);
	syntax_err = validate_syntax(shell->token_list);
	if (syntax_err != SYNTAX_OK)
	{
		syntax_error(syntax_err);
		shell->exit_status = 1;
		free_all(shell);
		return ;
	}
	shell->command_list = parser(shell->token_list);
	// var_expand(shell);
	executor(shell);
	free_all(shell);
}

char	*prompt(void)
{
	char	*line;
	char	*next_line;
	char	*temp;
	char	*joined;

	line = readline("\001\033[1;36m\002minishell$ \001\033[0m\002");
	if (!line)
		return (NULL);
	while (has_unclosed_quotes(line))
	{
		next_line = readline("> ");
		if (!next_line)
			break ;
		temp = ft_strjoin(line, "\n");
		joined = ft_strjoin(temp, next_line);
		free(temp);
		free(line);
		free(next_line);
		line = joined;
	}
	return (line);
}

int	has_unclosed_quotes(const char *input)
{
	int	s_quote;
	int	d_quote;

	s_quote = 0;
	d_quote = 0;
	while (*input)
	{
		if (*input == '\'' && d_quote == 0)
			s_quote = !s_quote;
		else if (*input == '"' && s_quote == 0)
			d_quote = !d_quote;
		input++;
	}
	return (s_quote || d_quote);
}
