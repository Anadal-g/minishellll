/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_iteration.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinamc <carolinamc@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:24:16 by anadal-g          #+#    #+#             */
/*   Updated: 2025/07/25 12:41:21 by carolinamc       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

pid_t	handle_cmd_iteration(t_token *current, t_env **env,
									int *prev_fd)
{
	int			curr_fd[2];
	pid_t		pid;
	pid_t		last_pid;
	int			is_last;
	t_pipe_fds	pipe_fds;

	if (current->next && pipe(curr_fd) < 0)
		exit_fork_pipe(PIPE);
	pid = fork();
	if (pid < 0)
		exit_fork_pipe(FORK);
	if (pid == 0)
	{
		is_last = current->next == NULL;
		execute_pipeline_child(current, env, &pipe_fds, is_last);
	}
	update_fds_and_pid(prev_fd, curr_fd, current, pid);
	last_pid = -1;
	if (!current->next)
		last_pid = pid;
	return (last_pid);
}

void	execute_child_external(t_token *current, t_env **env)
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
