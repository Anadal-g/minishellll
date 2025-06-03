/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:42:16 by mmendiol          #+#    #+#             */
/*   Updated: 2024/10/18 19:15:40 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ADDITIONAL_H
# define ADDITIONAL_H

# include "./libft.h"

// FUNCTIONS ADDED LATER
int		free_matrix_bool(char **str);
void	free_matrix(char **matrix);
int		ft_strchr_bool(const char *s, int c);
int		character_finder(char str, char c);
void	jump_character(char *input, int *counter, char c, int flag);
int		is_redir(char *str, int i);

#endif