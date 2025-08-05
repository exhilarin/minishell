/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:53:57 by mugenan           #+#    #+#             */
/*   Updated: 2025/08/05 20:33:31 by iguney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *env[])
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	(void)env;
	shell.exit_status = 0;
	while (1)
	{
		shell.input = prompt();
		if (!shell.input)
		{
			printf("exit\n");
			free(shell.input);
			break ;
		}
		if (*shell.input)
			add_history(shell.input);
		process(&shell);
	}
	return (0);
}

void	print_commands(t_cmd *commands)
{
	int		i;
	t_cmd	*cmd = commands;

	while (cmd)
	{
		printf("Command:\n");
		if (cmd->argv)
		{
			for (i = 0; cmd->argv[i]; i++)
				printf("  argv[%d]: %s\n", i, cmd->argv[i]);
		}
		else
			printf("  (No arguments)\n");

		t_redir *redir = cmd->redir;
		while (redir)
		{
			char *type_str = NULL;
			if (redir->type == REDIR_IN)
				type_str = "REDIR_IN";
			else if (redir->type == REDIR_OUT)
				type_str = "REDIR_OUT";
			else if (redir->type == APPEND)
				type_str = "APPEND";
			else if (redir->type == HEREDOC)
				type_str = "HEREDOC";

			printf("  redir: %s -> %s\n", type_str, redir->file);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}

void	process(t_shell *shell)
{
	int		syntax_err;

	if (is_invalid_char(shell->input))
	{
		shell->exit_status = 1;
		return (syntax_error(ERR_INVALID));
	}
	shell->token_list = lexer(shell->input);
	syntax_err = validate_syntax(shell->token_list);
	if (syntax_err != SYNTAX_OK)
	{
		syntax_error(syntax_err);
		shell->exit_status = 1;
		free_tokens(shell->token_list);
		return ;
	}
	shell->command_list = parser(shell->token_list);
	print_commands(shell->command_list);
	executor(shell, shell->command_list);
	shutdown_shell(shell);
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
