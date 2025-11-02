/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 13:53:36 by anadal-g          #+#    #+#             */
/*   Updated: 2025/11/02 19:09:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remove_redirection_tokens(char **tokens)
{
	int	i;
	int	j;

	if (!tokens)
		return ;
	i = 0;
	while (tokens[i])
	{
		if (!ft_strcmp(tokens[i], "<") || !ft_strcmp(tokens[i], "<<")
			|| !ft_strcmp(tokens[i], ">") || !ft_strcmp(tokens[i], ">>"))
		{
			free(tokens[i]);
			if (tokens[i + 1])
				free(tokens[i + 1]);
			j = i;
			while (tokens[j + 2])
			{
				tokens[j] = tokens[j + 2];
				j++;
			}
			tokens[j] = NULL;
			continue ;
		}
		i++;
	}
}

void	parse_redirections(t_token *token)
{
	if (!token)
		return ;
	detect_redirections(token);
	remove_redirection_tokens(token->tokens);
}
