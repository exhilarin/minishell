/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 18:10:34 by mugenan           #+#    #+#             */
/*   Updated: 2025/08/27 19:46:38 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_redir_context
{
	int		stdin_backup;
	int		stdout_backup;
	int		error;
	t_shell	*shell;
}	t_redir_context;

static int	backup_fds(t_redir_context *ctx)
{
	ctx->stdin_backup = dup(STDIN_FILENO);
	ctx->stdout_backup = dup(STDOUT_FILENO);
	if (ctx->stdin_backup == -1 || ctx->stdout_backup == -1)
	{
		if (ctx->stdin_backup != -1)
			close(ctx->stdin_backup);
		if (ctx->stdout_backup != -1)
			close(ctx->stdout_backup);
		exit_status_manager(1, 1);
		return (0);
	}
	return (1);
}

static void	process_redir_in(t_redir *redir, int *error)
{
	int	fd;

	fd = open(redir->file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(redir->file, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		*error = 1;
	}
	else
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			*error = 1;
		close(fd);
	}
}

static void	process_redir_out_or_append(t_redir *redir, int *error, int flags)
{
	int	fd;

	fd = open(redir->file, flags, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(redir->file, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		*error = 1;
	}
	else
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			*error = 1;
		close(fd);
	}
}

static void	process_redirections(t_redir_context *ctx, t_redir *redir)
{
	ctx->error = 0;
	while (redir && !ctx->error)
	{
		if (redir->type == REDIR_IN)
			process_redir_in(redir, &ctx->error);
		else if (redir->type == REDIR_OUT)
			process_redir_out_or_append(redir, &ctx->error,
				O_CREAT | O_WRONLY | O_TRUNC);
		else if (redir->type == APPEND)
			process_redir_out_or_append(redir, &ctx->error,
				O_CREAT | O_WRONLY | O_APPEND);
		else if (redir->type == HEREDOC)
		{
			if (redir_heredoc(ctx->shell, redir))
				ctx->error = 1;
		}
		redir = redir->next;
	}
}

static void	restore_fds_on_error(t_redir_context *ctx)
{
	if (dup2(ctx->stdin_backup, STDIN_FILENO) == -1
		|| dup2(ctx->stdout_backup, STDOUT_FILENO) == -1)
	{
		close(ctx->stdin_backup);
		close(ctx->stdout_backup);
		exit_status_manager(1, 1);
		return ;
	}
	close(ctx->stdin_backup);
	close(ctx->stdout_backup);
	if (ctx->error)
		exit_status_manager(1, 1);
}

static void	restore_fds_final(t_redir_context *ctx)
{
	if (dup2(ctx->stdin_backup, STDIN_FILENO) == -1
		|| dup2(ctx->stdout_backup, STDOUT_FILENO) == -1)
	{
		close(ctx->stdin_backup);
		close(ctx->stdout_backup);
		exit_status_manager(1, 1);
		return ;
	}
	close(ctx->stdin_backup);
	close(ctx->stdout_backup);
}

void	exec_builtin_with_redir(t_shell *shell, t_cmd *cmd)
{
	t_redir_context	ctx;

	ctx.shell = shell;
	if (!backup_fds(&ctx))
		return ;
	process_redirections(&ctx, cmd->redir);
	if (exit_status_manager(0, 0) == 130 || ctx.error)
	{
		restore_fds_on_error(&ctx);
		return ;
	}
	exec_builtin(shell, cmd);
	restore_fds_final(&ctx);
}

static void	redir_in(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(redir->file, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
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
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(redir->file, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
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
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(redir->file, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
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
