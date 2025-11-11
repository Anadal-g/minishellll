/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 11:48:41 by anadal-g          #+#    #+#             */
/*   Updated: 2025/11/11 11:48:41 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_unused_pipes(int *prev_fd, int *curr_fd, int fd_in, int fd_out,
		int is_last)
{
	if (prev_fd[0] != -1 && fd_in != prev_fd[0])
		close(prev_fd[0]);
	if (prev_fd[1] != -1)
		close(prev_fd[1]);
	if (!is_last)
	{
		if (fd_out != curr_fd[1])
			close(curr_fd[1]);
		close(curr_fd[0]);
	}
}

void	exec_pipeline_builtin(t_token *current, t_env **env)
{
	select_builtin(&current, env, current->command);
	exit((*env)->last_out);
}
