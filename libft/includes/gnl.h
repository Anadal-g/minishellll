/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmntrix <lmntrix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:37:28 by mmendiol          #+#    #+#             */
/*   Updated: 2024/09/28 10:49:07 by lmntrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H

# include "./libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

// FUNCTIONS GET_NEXT_LINE
void	free_all(char **to_free);
void	relocate_line(char **str_static, char **front);
char	*read_till_find(int fd, char *str_static);
char	*get_next_line(int fd);

// UTILS FUNCTIONS GET_NEXT_LINE
int		ft_strlen_gnl(const char *str);
int		ft_strchr_gnl(const char *s, int c);
char	*ft_strjoin_gnl(char *main, char *buffer);
char	*ft_substr_gnl(char *s, unsigned int start, size_t len);

#endif