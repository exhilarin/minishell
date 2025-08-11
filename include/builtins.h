/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:19:24 by iguney            #+#    #+#             */
/*   Updated: 2025/08/11 21:38:16 by mugenan          ###   ########.fr       */
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

int		is_builtin(t_cmd *cmd);
int		exec_builtin(t_shell *shell);
int		builtins_on_parent(char *name);

int		builtin_echo(char **args);
int		builtin_exit(char **args, t_shell *shell);
int		builtin_env(t_env *env);
int		builtin_export(t_env *env);

t_env	*new_env_node(char *env_str);
char	**env_list_to_array(t_env *env);
char	*get_env_value(t_env *env, char *key);

#endif
