/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:46:22 by anadal-g          #+#    #+#             */
/*   Updated: 2025/03/27 11:57:07 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Determina el tipo de redirección basado en el token
enum e_iotype	get_redirection_type(char *token)
{
	if (!token)
		return (-1);
	if (ft_strcmp(token, "<") == 0)
		return (INFILE);
	else if (ft_strcmp(token, "<<") == 0)
		return (HEREDOC);
	else if (ft_strcmp(token, ">") == 0)
		return (TRUNC);
	else if (ft_strcmp(token, ">>") == 0)
		return (APPEND);
	else
		return (-1);
}

// Añade un archivo de entrada/salida a la lista correspondiente
void	add_iofile(t_iofile **list, char *filename, enum e_iotype type)
{
	t_iofile *new;
	t_iofile *last;

	if (!filename || !list)
		return ;

	new = malloc(sizeof(t_iofile));
	if (!new)
	{
		perror("malloc");
		return ;
	}
	new->name = ft_strdup(filename);
	new->type = type;
	new->fd = -1;
	new->next = NULL;
	new->prev = NULL;

	if (!*list)
	{
		*list = new;
		return ;
	}
	last = *list;
	while (last->next)
		last = last->next;

	last->next = new;
	new->prev = last;
}
