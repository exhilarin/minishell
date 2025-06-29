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
}   t_token_type;

typedef struct s_token 
{
	t_token_type	type;
	char			*value;
	int 			quoted;
	struct s_token	*next;
}   t_token;

t_token	*lexer(char *input);
void	add_token(t_token **tokens, t_token_type type, char *value, int quoted);
void	handle_redirection(t_token **tokens, char **input);
char	*extract_quoted_string(char **input);
char	*extract_word(char **input);

int		ft_isspace(char c);
void	skip_whitespace(char **input);


#endif