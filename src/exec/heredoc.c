/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:31:45 by anadal-g          #+#    #+#             */
/*   Updated: 2025/11/11 12:54:51 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*create_heredoc_filename(void)
{
	static int	heredoc_count = 0;
	char		*tmp_file;

	tmp_file = malloc(200);
	if (!tmp_file)
		return (NULL);
	snprintf(tmp_file, 200, "/tmp/minishell_heredoc_%d_%d", getpid(),
		heredoc_count++);
	return (tmp_file);
}

static int	open_heredoc_file(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("heredoc open");
		free(filename);
		return (-1);
	}
	return (fd);
}

static void	write_heredoc_line(int fd, char *line)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}

static int	read_heredoc_lines(int fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("minishell: warning: here-document delimited"
				"by end-of-file\n", STDERR_FILENO);
			return (1);
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			return (1);
		}
		write_heredoc_line(fd, line);
		free(line);
	}
	return (0);
}

char	*heredoc(char *delimiter)
{
	int		fd;
	char	*tmp_file;

	if (!delimiter || !*delimiter)
	{
		ft_putstr_fd("minishell: invalid heredoc delimiter\n", STDERR_FILENO);
		return (NULL);
	}
	tmp_file = create_heredoc_filename();
	if (!tmp_file)
		return (NULL);
	fd = open_heredoc_file(tmp_file);
	if (fd == -1)
		return (NULL);
	read_heredoc_lines(fd, delimiter);
	close(fd);
	return (tmp_file);
}
