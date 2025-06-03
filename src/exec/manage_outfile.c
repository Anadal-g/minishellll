/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_outfile.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:10:58 by anadal-g          #+#    #+#             */
/*   Updated: 2025/06/02 12:54:12 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
static int aux_open_outfile(t_iofile *outfile, int i, int count, int *error)
{
    int fd;

    fd = -1;
    if (outfile->type == TRUNC)
        fd = open(outfile->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    else if (outfile->type == APPEND)
        fd = open(outfile->name, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd < 0)
    {
        perror(outfile->name); // CORRECCIÓN: No usar perror_error
        *error = 1;
    }
    // CORRECCIÓN: Solo cerrar si fd es válido
    if (i != count - 1 && fd >= 0)
    {
        close(fd);
        fd = -1;
    }
    return (fd);
}


static int	process_outfiles(t_iofile *outfiles, int count, int *error)
{
	int			fd;
	int			index;
	t_iofile	*current;

	fd = -1;
	index = 0;
	current = outfiles;
	while (current)
	{
		fd = aux_open_outfile(current, index, count, error);
		current = current->next;
		index++;
	}
	return (fd);
}

static int	count_outfiles(t_iofile *outfiles)
{
	int			count;
	t_iofile	*current;

	count = 0;
	current = outfiles;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

int	open_outfile(t_iofile *outfiles)
{
	int	fd;
	int	error;
	int	count;

	fd = -1;
	error = 0;
	if (!outfiles)
		return (STDOUT_FILENO);
	count = count_outfiles(outfiles);
	fd = process_outfiles(outfiles, count, &error);
	if (error == 1 && fd > 0)
	{
		close(fd);
		fd = -1;
	}
	return (fd);
}
