/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 17:01:43 by mmendiol          #+#    #+#             */
/*   Updated: 2025/03/27 11:56:44 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	rebuild_command(t_token *token)
{
	int		i;
	char	*new_command;
	char	*tmp;

	i = 0;
	new_command = ft_strdup("");
	while (token->tokens[i])
	{
		tmp = new_command;
		new_command = ft_strjoin(new_command, token->tokens[i]);
		free(tmp);
		if (token->tokens[i + 1])
		{
			tmp = new_command;
			new_command = ft_strjoin(new_command, " ");
			free(tmp);
		}
		i++;
	}
	free(token->command);
	token->command = new_command;
}

void	detect_redirections(t_token *token)
{
	int i = 0;
	enum e_iotype type;

	while (token->tokens[i])
	{
		type = get_redirection_type(token->tokens[i]);
		if ((int)type == -1)
		{
			i++;
			continue ;
		}
		if (token->tokens[i + 1])
		{
			if (type == INFILE || type == HEREDOC)
				add_iofile(&token->infile, token->tokens[i + 1], type);
			else
				add_iofile(&token->outfile, token->tokens[i + 1], type);
		}
		i += 2;
	}
}
