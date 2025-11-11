/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:20:05 by mmendiol          #+#    #+#             */
/*   Updated: 2025/11/11 11:32:14 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_n_flag(char *str)
{
	int	i;

	if (!str || str[0] != '-' || !str[1])
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	do_echo(t_token *token)
{
	int	i;
	int	newline;

	if (!token || !token->tokens)
		return (0);
	newline = 1;
	i = 1;
	while (token->tokens[i] && is_n_flag(token->tokens[i]))
	{
		newline = 0;
		i++;
	}
	while (token->tokens[i])
	{
		printf("%s", token->tokens[i]);
		if (token->tokens[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}
