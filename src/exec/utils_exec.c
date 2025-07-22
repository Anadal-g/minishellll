/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinamc <carolinamc@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:14:11 by anadal-g          #+#    #+#             */
/*   Updated: 2025/07/22 13:59:16 by carolinamc       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	validate_token(t_token *token)
{
	if (!token)
		return (0);
	if (!token->tokens)
		return (0);
	if (!token->tokens[0])
		return (0);
	if (!token->command)
		return (0);
	return (1);
}

void	read_till_character_redir(char *input, int *start, int *counter)
{
	if (!input || !start || !counter)
		return ;
	*counter = *start;
	while (input[*counter])
	{
		if (input[*counter] == '<' || input[*counter] == '>')
			break ;
		(*counter)++;
	}
}

int	handle_trim_and_store(char *substr, char **dest)
{
	char	*trimmed;

	trimmed = ft_strtrim(substr, " ");
	free(substr);
	if (!trimmed)
		return (0);
	*dest = trimmed;
	return (1);
}
