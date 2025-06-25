/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:31:45 by anadal-g          #+#    #+#             */
/*   Updated: 2025/06/25 13:34:58 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *heredoc(char *delimiter)
{
	int fd;
	char *tmp_file;
	char *line;
	static int heredoc_count = 0;
	
	if (!delimiter || !*delimiter)
	{
		ft_putstr_fd("minishell: invalid heredoc delimiter\n", STDERR_FILENO);
		return (NULL);
	}
	
	tmp_file = malloc(200);
	if (!tmp_file)
		return (NULL);
		
	snprintf(tmp_file, 200, "/tmp/minishell_heredoc_%d_%d", getpid(), heredoc_count++);
	
	fd = open(tmp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("heredoc open");
		free(tmp_file);
		return (NULL);
	}
	
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("minishell: warning: here-document delimited by end-of-file\n", STDERR_FILENO);
			break;
		}
		
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break;
		}
		
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	
	close(fd);
	return (tmp_file);
}