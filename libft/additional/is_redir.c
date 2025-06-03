/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:11:58 by mmendiol          #+#    #+#             */
/*   Updated: 2024/10/18 19:12:14 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	is_redir(char *str, int i)
{
	if (str[i] == '<' && str[i + 1] == '<')
		return (2);
	else if (str[i] == '>' && str[i + 1] == '>')
		return (2);
	else if (str[i] == '<' || str[i] == '>')
		return (1);
	return (0);
}
