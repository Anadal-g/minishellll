/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmntrix <lmntrix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 18:01:06 by mmendiol          #+#    #+#             */
/*   Updated: 2024/09/28 10:29:57 by lmntrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

long	ft_atol(const char *str)
{
	int		i;
	long	n;
	int		size_sign;

	i = 0;
	n = 0;
	size_sign = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			size_sign++;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		n = (n * 10) + (str[i++] - '0');
	if (size_sign == 1)
		n *= -1;
	return (n);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	*str1 = "--54";
// 	char	*str2 = "   			a	+48";
// 	char	*str3 = "-47";
// 	char	*str4 = "+47";
// 	char	*str5 = "2147483650";
// 	char	*str6 = "-2147483648";

// 	printf("%ld\n", ft_atol(str1));
// 	printf("%ld\n", atol(str1));
// 	printf("%ld\n", ft_atol(str2));
// 	printf("%ld\n", atol(str2));
// 	printf("%ld\n", ft_atol(str3));
// 	printf("%ld\n", atol(str3));
// 	printf("%ld\n", ft_atol(str4));
// 	printf("%ld\n", atol(str4));
// 	printf("%ld\n", ft_atol(str5));
// 	printf("%ld\n", atol(str5));
// 	printf("%ld\n", ft_atol(str6));
// 	printf("%ld\n", atol(str6));
// 	return (0);
// }
