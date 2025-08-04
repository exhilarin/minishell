/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:53:57 by mugenan           #+#    #+#             */
/*   Updated: 2025/08/04 07:11:54 by iguney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *env[])
{
	char	*input;

	(void)argc;
	(void)argv;
	(void)env;
	while (1)
	{
		input = prompt();
		if (!input)
		{
			printf("exit\n");
			free(input);
			break ;
		}
		if (*input)
			add_history(input);
		process(input);
	}
	return (0);
}

void	process(char *input)
{
	t_token	*token_list;
	t_cmd	*command_list;
	int		syntax_err;

	if (is_invalid_char(input))
		return (syntax_error(ERR_INVALID));
	token_list = lexer(input);
	syntax_err = validate_syntax(token_list);
	if (syntax_err != SYNTAX_OK)
	{
		syntax_error(syntax_err);
		free_tokens(token_list);
		return ;
	}
	command_list = parser(token_list);
	executor(command_list);
	free_tokens(token_list);
	free_cmd(command_list);
	free(input);
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
