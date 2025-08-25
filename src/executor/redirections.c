#include "minishell.h"

void	exec_builtin_with_redir(t_shell *shell, t_cmd *cmd)
{
	int	stdin_backup;
	int	stdout_backup;

	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	if (stdin_backup == -1 || stdout_backup == -1)
		exit_shell(1, "minishell: dup failed\n");
	if (cmd->redir)
		handle_redirections(shell, cmd->redir, 1);
	if (shell->exit_status == 130)
		return ;
	exec_builtin(shell, cmd);
	if (dup2(stdin_backup, STDIN_FILENO) == -1
		|| dup2(stdout_backup, STDOUT_FILENO) == -1)
		exit_shell(1, "minishell: dup2 failed\n");
	close(stdin_backup);
	close(stdout_backup);
}

static void	redir_in(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: No such file or directory: ", STDERR_FILENO);
		ft_putendl_fd(redir->file, STDERR_FILENO);
		exit_shell(1, NULL);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
		exit_shell(1, "minishell: dup2 failed\n");
	close(fd);
}

static void	redir_out(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: Permission denied: ", STDERR_FILENO);
		ft_putendl_fd(redir->file, STDERR_FILENO);
		exit_shell(1, NULL);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
		exit_shell(1, "minishell: dup2 failed\n");
	close(fd);
}

static void	redir_append(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: Permission denied: ", STDERR_FILENO);
		ft_putendl_fd(redir->file, STDERR_FILENO);
		exit_shell(1, NULL);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
		exit_shell(1, "minishell: dup2 failed\n");
	close(fd);
}

void	handle_redirections(t_shell *shell, t_redir *redir, int process)
{
	while (redir)
	{
		if (redir->type == REDIR_IN)
			redir_in(redir);
		else if (redir->type == REDIR_OUT)
			redir_out(redir);
		else if (redir->type == APPEND)
			redir_append(redir);
		else if (redir->type == HEREDOC && process == 1)
			redir_heredoc(shell, redir);
		redir = redir->next;
	}
}
