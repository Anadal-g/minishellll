/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinamc <carolinamc@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:14:11 by anadal-g          #+#    #+#             */
/*   Updated: 2025/07/25 12:03:36 by carolinamc       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	dup_builtin_fds(int fd_in, int fd_out,
							int *saved_stdin, int *saved_stdout)
{
	if (fd_in != STDIN_FILENO && fd_in >= 0)
	{
		*saved_stdin = dup(STDIN_FILENO);
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (fd_out != STDOUT_FILENO && fd_out >= 0)
	{
		*saved_stdout = dup(STDOUT_FILENO);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
}

void	restore_builtin_fds(int saved_stdin, int saved_stdout)
{
	if (saved_stdin >= 0)
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
	if (saved_stdout >= 0)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
}

int	open_builtin_fds(t_token *token, t_env **env,
							int *fd_in, int *fd_out)
{
	*fd_in = open_infile(token->infile);
	if (*fd_in < 0 && token->infile)
	{
		(*env)->last_out = 1;
		return (0);
	}
	*fd_out = open_outfile(token->outfile);
	if (*fd_out < 0 && token->outfile)
	{
		if (*fd_in >= 0 && *fd_in != STDIN_FILENO)
			close(*fd_in);
		(*env)->last_out = 1;
		return (0);
	}
	return (1);
}

void	close_pipe(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

void	close_child_pipes(t_child_io_context *ctx)
{
	if (ctx->prev_fd[0] != -1 && ctx->fd_in != ctx->prev_fd[0])
		close(ctx->prev_fd[0]);
	if (ctx->prev_fd[1] != -1)
		close(ctx->prev_fd[1]);
	if (!ctx->is_last)
	{
		if (ctx->fd_out != ctx->curr_fd[1])
			close(ctx->curr_fd[1]);
		close(ctx->curr_fd[0]);
	}
}
