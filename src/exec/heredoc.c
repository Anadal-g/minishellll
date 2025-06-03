/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:31:45 by anadal-g          #+#    #+#             */
/*   Updated: 2025/06/03 12:42:55 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int read_heredoc_input(int fd, char *delimiter_input)
{
    char *line;
    char *delimiter;
    int result = 1;

    if (!delimiter_input)
        return (0);
    delimiter = ft_strjoin(delimiter_input, "\n");
    if (!delimiter)
    {
        ft_putstr_fd("minishell: memory allocation error\n", STDERR_FILENO);
        return (0);
    }
    while (1)
    {
        line = readline("> ");
        if (!line) // EOF (Ctrl+D)
        {
            ft_putstr_fd("minishell: warning: here-document delimited by end-of-file\n", STDERR_FILENO);
            break;
        }
        char *line_with_newline = ft_strjoin(line, "\n");
        free(line);
        
        if (!line_with_newline)
        {
            result = 0;
            break;
        }
        if (ft_strcmp(line_with_newline, delimiter) == 0)
        {
            free(line_with_newline);
            break;
        }
        write(fd, line_with_newline, ft_strlen(line_with_newline));
        free(line_with_newline);
    }
    free(delimiter);
    return (result);
}

char *heredoc(char *delimiter)
{
    int fd;
    char *tmp_file;
    static int heredoc_count = 0;
    
    if (!delimiter)
        return (NULL);
    
    // CORRECCIÓN: Usar tamaño más seguro y validar malloc
    tmp_file = malloc(150);
    if (!tmp_file)
    {
        ft_putstr_fd("minishell: memory allocation error\n", STDERR_FILENO);
        return (NULL);
    }
    
    snprintf(tmp_file, 150, "/tmp/minishell_heredoc_%d_%d.tmp", 
             getpid(), heredoc_count++);
    
    fd = open(tmp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        perror("minishell: heredoc");
        free(tmp_file);
        return (NULL);
    }
    
    if (!read_heredoc_input(fd, delimiter))
    {
        close(fd);
        unlink(tmp_file);
        free(tmp_file);
        return (NULL);
    }
    
    close(fd);
    return (tmp_file);
}
