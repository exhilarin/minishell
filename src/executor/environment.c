/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 22:42:30 by mugenan           #+#    #+#             */
/*   Updated: 2025/08/27 19:46:38 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_envp(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return ;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

int	ms_is_valid_key(const char *s)
{
	int	i;

	if (!s || !(ft_isalpha((unsigned char)s[0]) || s[0] == '_'))
		return (0);
	i = 1;
	while (s[i] && s[i] != '=' && !(s[i] == '+' && s[i + 1] == '='))
	{
		if (!(ft_isalnum((unsigned char)s[i]) || s[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

int	ms_has_plus_equal(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] && s[i] != '=')
	{
		if (s[i] == '+' && s[i + 1] == '=')
			return (1);
		i++;
	}
	return (0);
}

char	*ms_key_from_arg(const char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		if (arg[i] == '+' && arg[i + 1] == '=')
			break ;
		i++;
	}
	return (ft_substr(arg, 0, i));
}

char	*ms_val_from_arg(const char *arg)
{
	char	*eq;

	eq = ft_strchr(arg, '=');
	if (!eq)
		return (NULL);
	return (ft_strdup(eq + 1));
}

char	*ms_strjoin_free(char *s1, char *s2)
{
	char	*result;

	if (!s1 || !s2)
		return (NULL);
	result = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (result);
}

char	*ms_join_kv(char *key, char *value)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(key, "=");
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, value);
	free(temp);
	return (result);
}

static t_env	*init_env_node(void)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->env_line = NULL;
	node->key = NULL;
	node->value = NULL;
	node->next = NULL;
	return (node);
}

static void	set_env_values(t_env *node, char *env_str, int eq_pos)
{
	if (env_str[eq_pos] == '=')
	{
		node->value = ft_strdup(env_str + eq_pos + 1);
		node->env_line = ft_strdup(env_str);
	}
	else
	{
		node->value = NULL;
		node->env_line = NULL;
	}
}

static t_env	*validate_env_allocs(t_env *node, char *env_str, int eq_pos)
{
	if (env_str[eq_pos] == '=' && !node->value)
		return (free(node->key), free(node), NULL);
	if (env_str[eq_pos] == '=' && !node->env_line)
		return (free(node->key), free(node->value), free(node), NULL);
	return (node);
}

t_env	*new_env_node(char *env_str)
{
	t_env	*node;
	int		i;

	node = init_env_node();
	if (!node)
		return (NULL);
	i = 0;
	while (env_str[i] && env_str[i] != '=')
		i++;
	node->key = ft_substr(env_str, 0, i);
	if (!node->key)
		return (free(node), NULL);
	set_env_values(node, env_str, i);
	return (validate_env_allocs(node, env_str, i));
}

static int	count_env_values(t_env *env)
{
	int		count;
	t_env	*curr;

	count = 0;
	curr = env;
	while (curr)
	{
		if (curr->value != NULL)
			count++;
		curr = curr->next;
	}
	return (count);
}

static char	**cleanup_envp_on_error(char **envp, int index)
{
	while (index-- > 0)
		free(envp[index]);
	free(envp);
	return (NULL);
}

static char	**fill_envp_array(t_env *env, char **envp)
{
	int	i;

	i = 0;
	while (env)
	{
		if (env->value != NULL)
		{
			envp[i] = ms_join_kv(env->key, env->value);
			if (!envp[i])
				return (cleanup_envp_on_error(envp, i));
			i++;
		}
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

char	**env_list_to_array(t_env *env)
{
	char	**envp;
	int		count;

	count = count_env_values(env);
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	return (fill_envp_array(env, envp));
}

char	*get_env_value(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		if (env->env_line)
			free(env->env_line);
		if (env->key)
			free(env->key);
		if (env->value)
			free(env->value);
		free(env);
		env = tmp;
	}
}
