/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_infile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinamc <carolinamc@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:24:36 by anadal-g          #+#    #+#             */
/*   Updated: 2025/07/22 13:22:10 by carolinamc       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_input_file(t_iofile *file)
{
	int		fd;
	char	*tmp_file;

	if (file->type == HEREDOC)
	{
		tmp_file = heredoc(file->name);
		if (!tmp_file)
			return (-1);
		fd = open(tmp_file, O_RDONLY);
		unlink(tmp_file);
		free(tmp_file);
	}
	else if (file->type == INFILE)
	{
		fd = open(file->name, O_RDONLY);
	}
	else
	{
		ft_putstr_fd("minishell: invalid redirection type\n", STDERR_FILENO);
		return (-1);
	}
	if (fd < 0)
		perror(file->name);
	return (fd);
}

int	open_infile(t_iofile *infiles)
{
	t_iofile	*current;
	int			fd;
	int			temp_fd;

	fd = STDIN_FILENO;
	if (!infiles)
		return (STDIN_FILENO);
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
		temp_fd = open_input_file(current);
		if (temp_fd < 0)
			return (-1);
		fd = temp_fd;
		current = current->next;
	}
	return (fd);
}
