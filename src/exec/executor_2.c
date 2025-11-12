/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:24:16 by anadal-g          #+#    #+#             */
/*   Updated: 2025/11/11 18:45:00 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	close_unused_pipes(t_pipeinfo *info)
{
	if (info->prev_fd[0] != -1 && info->fd_in != info->prev_fd[0])
		close(info->prev_fd[0]);
	if (info->prev_fd[1] != -1)
		close(info->prev_fd[1]);
	if (!info->is_last)
	{
		if (info->fd_out != info->curr_fd[1])
			close(info->curr_fd[1]);
		close(info->curr_fd[0]);
	}
}

void	exec_pipeline_builtin(t_token *current, t_env **env)
{
	select_builtin(&current, env, current->command);
	exit((*env)->last_out);
}
