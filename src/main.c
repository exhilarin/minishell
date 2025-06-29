/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:53:57 by mugenan           #+#    #+#             */
/*   Updated: 2025/06/29 20:54:08 by ilyas-guney      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//TODO: DELETE THESE: print_tokens & token_type_to_str

#include "../include/minishell.h"

int main(int argc, char *argv[], char *env[])
{
	(void)argc;
	(void)argv;
	(void)env;
	char *input;
	while (1)
	{
		input = prompt();
		if (!input)
		{
			printf("exit\n");
			free(input);
			break;
		}
		if (*input)
			add_history(input);
		process(input);
		free(input);
	}
	return (0);
}

void	process(char *input)
{
	t_token *token_list;
	t_cmd	*command_list;

	token_list = lexer(input);
	// command_list = parser(token_list);
	// executor(command_table);
	free_tokens(token_list);
    free_cmds(command_list);
	
}

char	*prompt(void)
{
	char	*line;
	char	*next_line;
	char	*temp;
	char	*joined;

	line  = readline("\001\033[1;36m\002minishell$ \001\033[0m\002");
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

/*  Sources

	https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf
	https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218
	https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html
	https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html
	https://github.com/Swoorup/mysh
*/

/*
	Your shell must implement the following built-in commands:
		◦ echo with option -n
		◦ cd with only a relative or absolute path
		◦ pwd with no options
		◦ export with no options
		◦ unset with no options
		◦ env with no options or arguments
		◦ exit with no options
*/

/*
	• Handle ’ (single quote) which should prevent the shell from interpreting the meta-
	characters in the quoted sequence.
	
	• Handle " (double quote) which should prevent the shell from interpreting the meta-
	characters in the quoted sequence except for $ (dollar sign).
*/

/*
	Implement the following redirections:
	◦ < should redirect input.
	◦ > should redirect output.
	◦ << should be given a delimiter, then read the input until a line containing the
	delimiter is seen. However, it doesn’t have to update the history!
	◦ >> should redirect output in append mode.
*/

/*
	• Implement pipes (| character). The output of each command in the pipeline is
	connected to the input of the next command via a pipe.
	• Handle environment variables ($ followed by a sequence of characters) whijch
	should expand to their values.
	• Handle $? which should expand to the exit status of the most recently executed
	foreground pipeline.
*/

/*
	• Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.
	• In interactive mode:
		◦ ctrl-C displays a new prompt on a new line.
		◦ ctrl-D exits the shell.
		◦ ctrl-\ does nothing.
*/