/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:19:13 by iguney            #+#    #+#             */
/*   Updated: 2025/08/27 23:31:45 by mugenan          ###   ########.fr       */
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
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	int				quoted;
	struct s_token	*next;
}	t_token;

t_token	*lexer(char *input);

void	skip_whitespace(char **input);
void	handle_redirection(t_token **tokens, char **input);

int		handle_word_token(t_token **tokens, char **input);
int		extract_word_with_quote(char **input, char **word);
int		handle_quote_char(char **input, char **result, int *quote_type);
int		handle_char(char **input, char **result);
int		process_word_chars(char **input, char **result, int *quote_type);
int		init_word_extraction(char **result, char **word);

char	*join_and_free(char *s1, char *s2);
char	*append_quoted_part(char **input, char *result, char quote);
int		ft_isspace(char c);
int		ft_strcmp(char *s1, char *s2);

void	add_token_with_quote(t_token **tokens, t_token_type type,
			char *value, int quote_type);
char	*add_quote_marker(char *result, char quote, char **input);
char	*add_end_marker(char *result, char **input);

#endif