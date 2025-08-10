/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:19:24 by iguney            #+#    #+#             */
/*   Updated: 2025/08/10 08:46:47 by iguney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct s_shell	t_shell;

typedef struct s_env
{
	char			*env_line;
	char			*key;
	char			*value;
	int				*is_exported;
	struct s_env	*next;
}	t_env;

int		builtin_echo(char **args);
int		builtin_exit(char **args, t_shell *shell);

int		builtin_env(t_env *env);
int		builtin_export(t_env *env);
void	init_env(t_shell *shell, char **envp);
char	**env_list_to_array(t_env *env);
char	*get_env_value(t_env *env, char *key);

#endif
