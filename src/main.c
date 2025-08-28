/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:53:57 by mugenan           #+#    #+#             */
/*   Updated: 2025/08/27 22:41:12 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *env[])
{
	t_shell	shell;

	(void)argv;
	if (argc != 1)
		return (0);
	set_get_shell(&shell);
	init_signal();
	init_shell(&shell);
	init_env(&shell, env);
	while (1)
	{
		g_signal_code = 0;
		shell.input = readline("\001\033[1;36m\002minishell$ \001\033[0m\002");
		if (!shell.input)
		{
			printf("exit\n");
			rl_clear_history();
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

	shell->token_list = lexer(shell->input);
	syntax_err = validate_syntax(shell, shell->token_list);
	if (syntax_err != SYNTAX_OK)
	{
		syntax_error(syntax_err);
		free_all(shell);
		return ;
	}
	shell->command_list = parser(shell->token_list);
	expand_all(shell);
	executor(shell, shell->command_list);
	free_all(shell);
}

t_shell	*set_get_shell(t_shell *sh)
{
	static t_shell	*shell = NULL;

	if (sh != NULL)
		shell = sh;
	return (shell);
}
