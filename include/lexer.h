/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:19:13 by iguney            #+#    #+#             */
/*   Updated: 2025/08/07 00:37:22 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND,
	VAR,
	QUOTE_SINGLE,
	QUOTE_DOUBLE
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	int				quoted;
	struct s_token	*next;
}	t_token;

t_token	*lexer(char *input);
void	add_token(t_token **tokens, t_token_type type, char *value, int quoted);
void	handle_redirection(t_token **tokens, char **input);
void	extract_double_quoted_string(t_token **tokens, char **input);
char	*extract_single_quoted_string(char **input);
char	*extract_word(char **input);
char	*extract_var(char **input);

int		ft_isspace(char c);
int		ft_strcmp(char *s1, char *s2);
void	skip_whitespace(char **input);

#endif