/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinamc <carolinamc@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:46:22 by anadal-g          #+#    #+#             */
/*   Updated: 2025/07/22 13:36:53 by carolinamc       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

t_iofile	*init_iofile_node(char *filename, enum e_iotype type)
{
	t_iofile	*new;

	new = malloc(sizeof(t_iofile));
	if (!new)
	{
		perror("malloc");
		return (NULL);
	}
	new->name = ft_strdup(filename);
	if (!new->name)
	{
		free(new);
		perror("ft_strdup");
		return (NULL);
	}
	new->type = type;
	new->fd = -1;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	add_iofile(t_iofile **list, char *filename, enum e_iotype type)
{
	t_iofile	*new;
	t_iofile	*last;

	if (!list || !filename || !*filename)
		return ;
	new = init_iofile_node(filename, type);
	if (!new)
		return ;
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
