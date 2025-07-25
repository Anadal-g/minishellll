/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinamc <carolinamc@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:24:16 by anadal-g          #+#    #+#             */
/*   Updated: 2025/07/25 12:36:49 by carolinamc       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_fds_and_pid(int *prev_fd, int *curr_fd,
								t_token *current, pid_t pid)
{
	(void)pid;
	if (prev_fd[0] != -1)
		close_pipe(prev_fd);
	if (current->next)
	{
		prev_fd[0] = curr_fd[0];
		prev_fd[1] = curr_fd[1];
	}
}

void	execute_child_builtin(t_token *current, t_env **env)
{
	select_builtin(&current, env, current->command);
	exit((*env)->last_out);
}

int	handle_child_input_fd(t_token *current, int *prev_fd)
{
	int	fd_in;

	fd_in = STDIN_FILENO;
	if (current->infile)
	{
		fd_in = open_infile(current->infile);
		if (fd_in < 0)
			exit(1);
	}
	else if (prev_fd[0] != -1)
	{
		fd_in = prev_fd[0];
	}
	return (fd_in);
}

int	handle_child_output_fd(t_token *current, int *curr_fd,
		int is_last, int fd_in_for_error_close)
{
	int	fd_out;

	fd_out = STDOUT_FILENO;
	if (current->outfile)
	{
		fd_out = open_outfile(current->outfile);
		if (fd_out < 0)
		{
			if (fd_in_for_error_close != STDIN_FILENO)
				close(fd_in_for_error_close);
			exit(1);
		}
	}
	else if (!is_last)
	{
		fd_out = curr_fd[1];
	}
	return (fd_out);
}
