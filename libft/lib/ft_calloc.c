/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:32:46 by mmendiol          #+#    #+#             */
/*   Updated: 2024/05/10 16:32:59 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*str;

	if (size != 0 && count > SIZE_MAX / size)
		return (NULL);
	str = malloc(count * size);
	if (!str)
		return (NULL);
	ft_bzero(str, count * size);
	return (str);
}

// int	main(void)
// {
// 	char		*s;
// 	size_t	num_e;

// 	num_e = 5;
// 	s = ft_calloc(num_e, sizeof(int));
// 	printf("Arreglo inicializado a cero:\n");
// 	while (num_e > 0)
// 	{
// 		printf("Mio[%zu] = %d\n", num_e, s[num_e]);
// 		num_e--;
// 	}
// 	free(s);
// 	return (0);
// }
