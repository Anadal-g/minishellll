/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jump_character.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:55:53 by mmendiol          #+#    #+#             */
/*   Updated: 2024/10/18 14:34:58 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	jump_character(char *input, int *counter, char c, int flag)
{
	if (flag)
		while (input[*counter] && character_finder(input[*counter], c))
			(*counter)++;
	else
		while (input[*counter] && !character_finder(input[*counter], c))
			(*counter)++;
}
