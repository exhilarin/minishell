/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:19:24 by iguney            #+#    #+#             */
/*   Updated: 2025/08/26 18:06:28 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

typedef struct s_shell	t_shell;

typedef struct s_env
{
	char			*env_line;
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

int		is_builtin(t_cmd *cmd);

void	builtin_pwd(void);
void	builtin_env(t_env *env);
void	builtin_exit(char **args);
void	builtin_echo(char **args);
void	builtin_cd(t_shell *shell, t_cmd *cmd);
void	builtin_unset(t_env **env, t_cmd *cmd);
void	exec_builtin(t_shell *shell, t_cmd *cmd);
void	builtin_export(t_shell *shell, t_cmd *cmd);

t_env	*new_env_node(char *env_str);
char	**env_list_to_array(t_env *env);
char	*get_env_value(t_env *env, char *key);
void	add_env_node(t_env **env, char *key, char *value);
void	set_env_value(t_env **env, char *key, char *value);

#endif
