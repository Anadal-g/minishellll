/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_infile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:24:36 by anadal-g          #+#    #+#             */
/*   Updated: 2025/11/11 11:46:16 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	open_heredoc_file(char *name)
{
	char	*tmp_file;
	int		temp_fd;

	tmp_file = heredoc(name);
	if (!tmp_file)
		return (-1);
	temp_fd = open(tmp_file, O_RDONLY);
	unlink(tmp_file);
	free(tmp_file);
	return (temp_fd);
}

static int	open_regular_infile(t_iofile *current)
{
	int	temp_fd;

	if (current->type == HEREDOC)
		temp_fd = open_heredoc_file(current->name);
	else if (current->type == INFILE)
		temp_fd = open(current->name, O_RDONLY);
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

int	open_infile(t_iofile *infiles)
{
	t_iofile	*current;
	int			fd;
	int			temp_fd;

	if (!infiles)
		return (STDIN_FILENO);
	fd = STDIN_FILENO;
	current = infiles;
	while (current)
	{
		if (!current->name)
		{
			ft_putstr_fd("minishell: invalid redirection\n", STDERR_FILENO);
			return (-1);
		}
		if (fd != STDIN_FILENO)
			close(fd);
		temp_fd = open_regular_infile(current);
		if (temp_fd < 0)
			return (-1);
		fd = temp_fd;
		current = current->next;
	}
	return (fd);
}
