/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinamc <carolinamc@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:24:16 by anadal-g          #+#    #+#             */
/*   Updated: 2025/07/25 12:42:40 by carolinamc       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_tokens(t_token *tokens)
{
	int		count;
	t_token	*current;

	count = 0;
	current = tokens;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

static void	one_command(t_token *token, t_env **env)
{
	if (!token || !token->tokens || !token->tokens[0])
		return ;
	if (is_builtin(token->tokens[0]))
		exe_built_ins(token, env);
	else
		exe_one_cmd(token, env);
}

void	execute_pipeline_child(t_token *current, t_env **env,
									t_pipe_fds *pipe_fds, int is_last)
{
	t_child_io_context	ctx;

	ctx.prev_fd[0] = pipe_fds->prev_fd[0];
	ctx.prev_fd[1] = pipe_fds->prev_fd[1];
	ctx.curr_fd[0] = pipe_fds->curr_fd[0];
	ctx.curr_fd[1] = pipe_fds->curr_fd[1];
	ctx.is_last = is_last;
	ctx.fd_in = handle_child_input_fd(current, ctx.prev_fd);
	ctx.fd_out = handle_child_output_fd(current, ctx.curr_fd,
			ctx.is_last, ctx.fd_in);
	close_child_pipes(&ctx);
	setup_child_io(ctx.fd_in, ctx.fd_out);
	if (is_builtin(current->tokens[0]))
	{
		execute_child_builtin(current, env);
	}
	else
	{
		execute_child_external(current, env);
	}
}

static void	two_or_more_cmds(t_token *tokens, t_env **env)
{
	t_token	*current;
	int		prev_fd[2];
	pid_t	last_pid;

	current = tokens;
	prev_fd[0] = -1;
	prev_fd[1] = -1;
	last_pid = -1;
	while (current)
	{
		last_pid = handle_cmd_iteration(current, env, prev_fd);
		current = current->next;
	}
	close_pipe(prev_fd);
	wait_childs(last_pid, &(*env)->last_out);
}

void	executor(t_token *tokens, t_env **env)
{
	int	cmd_count;

	if (!tokens)
		return ;
	cmd_count = count_tokens(tokens);
	if (cmd_count == 1)
		one_command(tokens, env);
	else
		two_or_more_cmds(tokens, env);
}
