/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:53:57 by mugenan           #+#    #+#             */
/*   Updated: 2025/08/15 02:59:37 by iguney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *env[])
{
	t_shell	shell;

	(void)argv;
	if (argc != 1)
		return (0);
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

	shell->token_list = lexer(shell->input);
	syntax_err = validate_syntax(shell, shell->token_list);
	if (syntax_err != SYNTAX_OK)
	{
		syntax_error(syntax_err);
		shell->exit_status = 1;
		free_all(shell);
		return ;
	}
	shell->command_list = parser(shell->token_list);
	expand_all(shell);
	executor(shell);
	free_all(shell);
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
