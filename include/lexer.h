/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:19:13 by iguney            #+#    #+#             */
/*   Updated: 2025/08/16 20:30:23 by iguney           ###   ########.fr       */
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

void	handle_redirection(t_token **tokens, char **input);
int		handle_word_token(t_token **tokens, char **input);
char	*extract_word(char **input);

char	*append_quoted_part(char **input, char *result, char quote);
char	*join_and_free(char *s1, char *s2);
int		ft_strcmp(char *s1, char *s2);
void	skip_whitespace(char **input);
int		ft_isspace(char c);

#endif