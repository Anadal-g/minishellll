/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_outfile.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:10:58 by anadal-g          #+#    #+#             */
/*   Updated: 2025/10/28 19:54:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int open_regular_outfile(t_iofile *current)
{
	int temp_fd;

	if (current->type == TRUNC)
		temp_fd = open(current->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (current->type == APPEND)
		temp_fd = open(current->name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
	{
		ft_putstr_fd("minishell: invalid redirection type\n", STDERR_FILENO);
		return (-1);
	}
	if (temp_fd < 0)
	{
		perror(current->name);
		return (-1);
	}
	return (temp_fd);
}

int open_outfile(t_iofile *outfiles)
{
	t_iofile *current;
	int fd;
	int temp_fd;

	if (!outfiles)
		return (STDOUT_FILENO);
	fd = STDOUT_FILENO;
	current = outfiles;
	while (current)
	{
		if (!current->name)
		{
			ft_putstr_fd("minishell: invalid redirection\n", STDERR_FILENO);
			return (-1);
		}
		if (fd != STDOUT_FILENO)
			close(fd);
		temp_fd = open_regular_outfile(current);
		if (temp_fd < 0)
			return (-1);
		fd = temp_fd;
		current = current->next;
	}
	return (fd);
}
