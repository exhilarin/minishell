/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:19:20 by iguney            #+#    #+#             */
/*   Updated: 2025/08/25 04:32:41 by iguney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <sys/types.h>
# include <sys/stat.h>

typedef struct s_shell	t_shell;

typedef struct s_exec
{
	int		flag;
	char	*cmd_path;
	char	**paths;
	char	**envp;
}	t_exec;

char	*handle_quoted_part(char **str, char quote);
char	*handle_quote(char **str, int *quote);
char	*handle_char(char *str, int *i);

void    expand_all(t_shell *shell);
void    expand_args(t_shell *shell, t_cmd *cmd);
void    expand_redirs(t_shell *shell, t_cmd *cmd);
char    *expand_string(t_shell *shell, char *str);
char    *expand_var(t_shell *shell, char *str, char **ptr_i);

void	executor(t_shell *shell, t_cmd *cmd);
void	exec_command(t_shell *shell, t_cmd *cmd);
void	child_process(t_shell *shell, t_cmd *cmd, int fd[2]);
void	parent_process(t_shell *shell, t_cmd *cmd, int fd[2], pid_t pid);

char	*get_cmd_path(t_shell *shell, t_cmd *cmd);
int		check_special_case(t_shell *shell, t_cmd *cmd, t_redir *redir);

void	exec_builtin_with_redir(t_shell *shell, t_cmd *cmd);
int		redir_heredoc(t_shell *shell, t_redir *redir);
int		handle_heredoc(t_shell *shell, t_redir *redir);
void	handle_redirections(t_shell *shell, t_redir *redir, int proccess);

#endif