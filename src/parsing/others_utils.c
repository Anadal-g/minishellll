/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinamc <carolinamc@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:02:31 by mmendiol          #+#    #+#             */
/*   Updated: 2025/07/21 16:00:49 by carolinamc       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_variable_name(char **str)
{
	char	*var_start;
	size_t	len;

	var_start = *str;
	len = 0;
	if (**str == '?')
	{
		(*str)++;
		return (ft_strdup("?"));
	}
	while (**str && (ft_isalnum(**str) || **str == '_'))
		(*str)++;
	len = *str - var_start;
	return (ft_strndup(var_start, len));
}

void	jump_character(char *str, int *counter, char c, int flag)
{
	if (flag == TRUE)
	{
		while (str[*counter] && str[*counter] == c)
			(*counter)++;
	}
	else
	{
		while (str[*counter] && str[*counter] != c)
			(*counter)++;
		if (str[*counter] == c)
			(*counter)++;
	}
}

void	read_till_character(char *input, int *start, int *counter, char c)
{
	char	quote;

	*start = *counter;
	while (input[*counter])
	{
		if (input[*counter] == DQUOTES || input[*counter] == SQUOTES)
		{
			quote = input[(*counter)++];
			jump_character(input, counter, quote, FALSE);
		}
		else if (character_finder(input[*counter], c))
			break ;
		(*counter)++;
	}
}
