/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_infile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:24:36 by anadal-g          #+#    #+#             */
/*   Updated: 2025/06/02 12:53:50 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int open_heredoc_infile(t_iofile *infile, int *error)
{
    int fd;
    char *name;

    name = heredoc(infile->name);
    if (!name)
    {
        perror("Error al procesar heredoc"); // CORRECCIÓN: No usar perror_error
        *error = 1;
        return (-1);
    }
    fd = open(name, O_RDONLY);
    if (fd < 0)
    {
        perror(name); // CORRECCIÓN: No usar perror_error
        *error = 1;
    }
    free(name); // CORRECCIÓN: Liberar el nombre del archivo
    return (fd);
}

static int open_normal_infile(t_iofile *infile, int *error)
{
    int fd;

    fd = open(infile->name, O_RDONLY);
    if (fd < 0)
    {
        perror(infile->name); // CORRECCIÓN: No usar perror_error
        *error = 1;
    }
    return (fd);
}

static int	aux_open_infile(t_iofile *infile, int i, int count, int *error)
{
	int	fd;

	fd = -1;
	if (infile->type == INFILE)
		fd = open_normal_infile(infile, error);
	else
		fd = open_heredoc_infile(infile, error);
	if (i != count - 1 && fd >= 0)
	{
		close(fd);
		fd = -1;
	}
	return (fd);
}
int open_infile(t_iofile *infiles)
{
    int fd = -1;
    int error = 0;
    int count, i;
    t_iofile *current;

    if (!infiles)
        return (STDIN_FILENO);
        
    // Contar archivos
    count = 0;
    current = infiles;
    while (current)
    {
        count++;
        current = current->next;
    }
    
    // Procesar archivos
    current = infiles;
    i = 0;
    while (current && i < count)
    {
        fd = aux_open_infile(current, i, count, &error);
        // CORRECCIÓN: Retornar inmediatamente si hay error
        if (error)
            return (-1);
        current = current->next;
        i++;
    }
    
    return (fd >= 0 ? fd : STDIN_FILENO);
}
