/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:50:23 by mmendiol          #+#    #+#             */
/*   Updated: 2024/10/03 17:39:30 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_realloc(void *ptr, size_t original_size, size_t new_size)
{
	void	*new_ptr;
	size_t	size_to_cpy;

	if (new_size == 0)
		return (free(ptr), NULL);
	new_ptr = ft_calloc(1, new_size + 1);
	if (!new_ptr)
		return (free(ptr), NULL);
	if (ptr)
	{
		if (original_size < new_size)
			size_to_cpy = original_size;
		else
			size_to_cpy = new_size;
		ft_memcpy(new_ptr, ptr, size_to_cpy);
		free(ptr);
	}
	return (new_ptr);
}
