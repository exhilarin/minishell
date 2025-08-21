/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:19:24 by iguney            #+#    #+#             */
/*   Updated: 2025/08/22 01:39:26 by ilyas-guney      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

typedef struct s_shell	t_shell;

typedef struct s_env
{
	char			*env_line;
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

int		is_builtin(t_cmd *cmd);
int		exec_builtin(t_shell *shell, t_cmd *cmd);

int		builtin_pwd(void);
int		builtin_env(t_env *env);
int		builtin_echo(char **args);
int		builtin_print_export(t_env *env);
int		builtin_cd(t_shell *shell, t_cmd *cmd);
int		builtin_unset(t_env **env, t_cmd *cmd);
int		builtin_export(t_env **env, t_cmd *cmd);
int		builtin_exit(char **args, t_shell *shell);

t_env	*new_env_node(char *env_str);
char	**env_list_to_array(t_env *env);
char	*get_env_value(t_env *env, char *key);

#endif
