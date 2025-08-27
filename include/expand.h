/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 21:58:31 by iguney            #+#    #+#             */
/*   Updated: 2025/08/27 23:31:31 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "minishell.h"

void	expand_all(t_shell *shell);
void	expand_args(t_shell *shell, t_cmd *cmd);
void	expand_redirs(t_shell *shell, t_cmd *cmd);
char	*expand_string(t_shell *shell, char *str);
char	*expand_var(t_shell *shell, char *str, char **ptr_i);

char	*handle_special_vars(char **ptr_i);
char	*handle_single_quotes(char **str_ptr);
char	*handle_double_quotes(t_shell *shell, char **str_ptr);
char	*handle_regular_char(t_shell *shell, char *str, char **str_ptr,
			int in_single_quotes);
void	handle_quote_chars(char **str_ptr, int *in_single_quotes);

int		is_simple_single_quote(char *str);
int		count_non_empty_args(char **argv);
char	**filter_empty_args(char **argv);
char	*extract_var_name(t_shell *shell, char **ptr_i);
void	copy_non_empty_args(char **argv, char **new_argv);

#endif