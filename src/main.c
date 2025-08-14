/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:53:57 by mugenan           #+#    #+#             */
/*   Updated: 2025/08/14 11:45:43 by iguney           ###   ########.fr       */
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
		shell.input = readline("\001\033[1;36m\002minishell$ \001\033[0m\002");
		if (!shell.input)
			return (shell.exit_status);
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
	expand(shell);
	executor(shell);
	free_all(shell);
}
