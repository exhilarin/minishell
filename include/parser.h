#ifndef PARSER_H
# define PARSER_H

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



#endif