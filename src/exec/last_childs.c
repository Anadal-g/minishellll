/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_childs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:28:31 by anadal-g          #+#    #+#             */
/*   Updated: 2025/11/11 11:46:21 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	setup_last_child(t_token *token, t_env *env, int fd_in, int fd_out)
{
	child_aux(token, env, fd_in, fd_out, 1);
}

void	last_child(t_token *token, t_env **env, int *fd)
{
	pid_t	pid;
	int		fd_in;
	int		fd_out;

	pid = fork();
	if (pid == -1)
	{
		perror("Error en fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		close(fd[1]);
		fd_in = open_infile(token->infile);
		if (fd_in < 0)
			fd_in = fd[0];
		else
			close(fd[0]);
		fd_out = open_outfile(token->outfile);
		if (fd_out < 0)
			fd_out = STDOUT_FILENO;
		setup_last_child(token, *env, fd_in, fd_out);
	}
	close(fd[0]);
	close(fd[1]);
}
