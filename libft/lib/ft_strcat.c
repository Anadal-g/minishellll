/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:10:31 by mmendiol          #+#    #+#             */
/*   Updated: 2024/10/03 17:39:38 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strcat(char *dest, const char *str)
{
	size_t	dest_len;
	size_t	i;

	dest_len = ft_strlen(dest);
	i = 0;
	while (str[i])
	{
		dest[dest_len + i] = str[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	dest[50];
	char	src[];
	char	dest2[];
	char	src2[];

	dest[50] = "lorem ipsum dolor sit amet";
	src[] = "hellofri";
	dest2[] = "lorem ipsum dolor sit amet";
	src2[] = "hellofri";
	printf("Mia: %zu %s\n", ft_strlcat(dest,src,15), dest);
	printf("Original: %lu %s\n", strlcat(dest2,src2,15), dest2);
	return (0);
}
*/
