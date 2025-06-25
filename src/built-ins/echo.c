/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:20:05 by mmendiol          #+#    #+#             */
/*   Updated: 2025/06/25 13:20:54 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int is_n_flag(char *arg)
{
	int i;
	
	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (0);
	i = 2;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int do_echo(t_token *token)
{
	int i;
	int newline;
	
	if (!token || !token->tokens)
		return (1);
		
	i = 1;
	newline = 1;
	
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
