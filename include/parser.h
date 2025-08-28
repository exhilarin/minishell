/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:16:33 by iguney            #+#    #+#             */
/*   Updated: 2025/08/28 04:04:06 by iguney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define SYNTAX_OK				0
# define ERR_INVALID			1
# define ERR_PIPE_START			2
# define ERR_PIPE_DOUBLE		3
# define ERR_REDIR_EOF			4
# define ERR_PIPE_EOF			5
# define ERR_UNCLOSED_QUOTES	6

typedef struct s_shell	t_shell;

typedef struct s_redir
{
	int				type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**argv;
	t_redir			*redir;
	struct s_cmd	*next;
}	t_cmd;

t_cmd	*parser(t_token *tokens);

char	*handle_single_quotes(char **str_ptr);
char	*expand_string(t_shell *shell, char *str);
char	*expand_var(t_shell *shell, char *str, char **ptr_i);
char	*handle_double_quotes(t_shell *shell, char **str_ptr);
void	expand_all(t_shell *shell);
void	expand_args(t_shell *shell, t_cmd *cmd);
void	expand_redirs(t_shell *shell, t_cmd *cmd);

void	syntax_error(int err_code);
int		is_invalid_char(char *input);
int		validate_redir(t_token *tokens);
int		is_unclosed_quotes(const char *input);
int		validate_syntax(t_shell *shell, t_token *tokens);
int		process_token(t_token **c_tkn, t_cmd **c_cmd, t_cmd **cmds);

#endif