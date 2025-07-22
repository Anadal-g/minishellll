/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinamc <carolinamc@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:31:45 by anadal-g          #+#    #+#             */
/*   Updated: 2025/07/22 12:05:24 by carolinamc       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	open_heredoc_file(char **tmp_file, int *fd, int count)
{
	*tmp_file = malloc(200);
	if (!*tmp_file)
		return (0);
	snprintf(*tmp_file, 200, "/tmp/minishell_heredoc_%d_%d", getpid(), count);
	*fd = open(*tmp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd == -1)
	{
		perror("heredoc open");
		free(*tmp_file);
		return (0);
	}
	return (1);
}

static void	read_heredoc_loop(int fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("minishell:delimited by end-of-file\n", STDERR_FILENO);
			break ;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

char	*heredoc(char *delimiter)
{
	int			fd;
	char		*tmp_file;
	static int	heredoc_count = 0;

	if (!delimiter || !*delimiter)
	{
		ft_putstr_fd("minishell: invalid heredoc delimiter\n", STDERR_FILENO);
		return (NULL);
	}
	if (!open_heredoc_file(&tmp_file, &fd, heredoc_count++))
		return (NULL);
	read_heredoc_loop(fd, delimiter);
	close(fd);
	return (tmp_file);
}
