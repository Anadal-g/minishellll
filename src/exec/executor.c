/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:24:16 by anadal-g          #+#    #+#             */
/*   Updated: 2025/11/12 11:01:01 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_pipeline_external(t_token *current, t_env **env)
{
	char	*path;
	char	**env_array;

	path = handle_command_path(current, *env, &env_array);
	if (!path)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(current->tokens[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		if (env_array)
			free_matrix(env_array);
		exit(127);
	}
	execve(path, current->tokens, env_array);
	perror("execve");
	free(path);
	if (env_array)
		free_matrix(env_array);
	exit(126);
}

void	execute_pipeline_child(t_token *current, t_env **env, int *prev_fd,
		int *curr_fd, int is_last)
{
	int	fd_in;
	int	fd_out;
	t_pipeinfo	info;
	
	fd_in = STDIN_FILENO;
	fd_out = STDOUT_FILENO;
	if (!setup_pipeline_input(current, prev_fd, &fd_in))
		exit(1);
	if (!setup_pipeline_output(current, curr_fd, &fd_out, is_last))
	{
		if (fd_in != STDIN_FILENO)
			close(fd_in);
		exit(1);
	}
	info.prev_fd = prev_fd;
	info.curr_fd = curr_fd;
	info.fd_in = fd_in;
	info.fd_out = fd_out;
	info.is_last = is_last;
	close_unused_pipes(&info);
	setup_child_io(fd_in, fd_out);
	if (is_builtin(current->tokens[0]))
		exec_pipeline_builtin(current, env);
	else
		exec_pipeline_external(current, env);
}

void	handle_parent_pipes(int *prev_fd, int *curr_fd, int has_next)
{
	if (prev_fd[0] != -1)
	{
		close(prev_fd[0]);
		close(prev_fd[1]);
	}
	if (has_next)
	{
		prev_fd[0] = curr_fd[0];
		prev_fd[1] = curr_fd[1];
	}
}

static void	close_and_wait(pid_t last_pid, int *prev_fd, t_env **env)
{
	if (prev_fd[0] != -1)
	{
		close(prev_fd[0]);
		close(prev_fd[1]);
	}
	wait_childs(last_pid, &(*env)->last_out);
}

static pid_t	fork_and_exec(t_token *cur, t_env **env, int *prev_fd, int *curr_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		exit_fork_pipe(FORK);
	if (pid == 0)
		execute_pipeline_child(cur, env, prev_fd, curr_fd, !cur->next);
	handle_parent_pipes(prev_fd, curr_fd, cur->next != NULL);
	return (pid);
}

void	two_or_more_cmds(t_token *tokens, t_env **env)
{
	t_token	*cur;
	int		prev_fd[2];
	int		curr_fd[2];
	pid_t	last_pid;

	prev_fd[0] = -1;
	prev_fd[1] = -1;
	last_pid = -1;
	cur = tokens;
	while (cur)
	{
		if (cur->next && pipe(curr_fd) < 0)
			exit_fork_pipe(PIPE);
		last_pid = fork_and_exec(cur, env, prev_fd, curr_fd);
		cur = cur->next;
	}
	close_and_wait(last_pid, prev_fd, env);
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
