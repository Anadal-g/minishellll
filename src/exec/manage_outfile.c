/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_outfile.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinamc <carolinamc@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:10:58 by anadal-g          #+#    #+#             */
/*   Updated: 2025/07/22 13:26:52 by carolinamc       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_output_file(t_iofile *file)
{
	int	fd;

	if (file->type == TRUNC)
		fd = open(file->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (file->type == APPEND)
		fd = open(file->name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
	{
		ft_putstr_fd("minishell: invalid redirection type\n", STDERR_FILENO);
		return (-1);
	}
	if (fd < 0)
		perror(file->name);
	return (fd);
}

int	open_outfile(t_iofile *outfiles)
{
	t_iofile	*current;
	int			fd;
	int			temp_fd;

	fd = STDOUT_FILENO;
	if (!outfiles)
		return (STDOUT_FILENO);
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
		temp_fd = open_output_file(current);
		if (temp_fd < 0)
			return (-1);
		fd = temp_fd;
		current = current->next;
	}
	return (fd);
}
