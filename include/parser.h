#ifndef PARSER_H
# define PARSER_H

#define SYNTAX_OK       0
#define ERR_INVALID		1
#define ERR_PIPE_START  2
#define ERR_PIPE_DOUBLE 3
#define ERR_REDIR_EOF   4
#define ERR_PIPE_EOF	5

typedef struct s_redir
{
	int				type;
	char			*file;
	struct s_redir	*next;
} t_redir;

typedef struct s_cmd
{
	char			**argv;
	t_redir			*redir;
	struct s_cmd	*next;
} t_cmd;

t_cmd	*parser(t_token *tokens);
int		process_token(t_token **token, t_cmd **curr, t_cmd **cmds, t_token *tokens);
t_cmd	*init_cmd(void);

int		is_invalid_char(char *input);
int		validate_syntax(t_token	*tokens);
void	syntax_error(int err_code);
void	free_tokens(t_token *tokens);
void	free_cmd(t_cmd  *commands);

#endif