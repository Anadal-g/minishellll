/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmntrix <lmntrix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:34:44 by mmendiol          #+#    #+#             */
/*   Updated: 2024/09/27 03:18:49 by lmntrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*dst;
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (len < (int)n && s[len])
	{
		len++;
	}
	dst = ft_calloc(len + 1, sizeof(char));
	if (!dst)
		return (NULL);
	while (s[i] && len > i)
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
