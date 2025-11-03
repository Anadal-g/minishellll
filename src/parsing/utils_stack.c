/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_stack.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:02:31 by mmendiol          #+#    #+#             */
/*   Updated: 2025/11/03 12:57:34 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	validate_command_syntax(char *command)
{
	int	i;

	i = 0;
	if (!command || !*command)
		return (0);
	while (command[i])
	{
		if (command[i] == '<' || command[i] == '>')
		{
			if (command[i] == command[i + 1])
				i++;
			i++;
			while (command[i] && (command[i] == ' ' || command[i] == '\t'))
				i++;
			if (!command[i] || command[i] == '<'
				|| command[i] == '>' || command[i] == '|')
			{
				ft_putstr_fd("minishell: unexpected token\n", STDERR_FILENO);
				return (0);
			}
		}
		else
			i++;
	}
	return (1);
}

static int	handle_command_allocation(t_token *tokens, char *command)
{
	tokens->command = ft_strdup(command);
	if (!tokens->command)
	{
		free(tokens);
		return (0);
	}
	return (1);
}

static int	handle_redirections(t_token *tokens, char *command)
{
	tokens->tokens = redir_divisor(command);
	if (!tokens->tokens)
	{
		free(tokens->command);
		free(tokens);
		return (0);
	}
	parse_redirections(tokens);
	return (1);
}

static int	handle_split(t_token *tokens, char *command)
{
	tokens->tokens = ft_split(command, ' ');
	if (!tokens->tokens)
	{
		free(tokens->command);
		free(tokens);
		return (0);
	}
	return (1);
}

t_token	*create_node(int id, char *command)
{
	t_token	*tokens;

	if (!command || !*command)
		return (NULL);
	if (!validate_command_syntax(command))
		return (NULL);
	tokens = ft_calloc(1, sizeof(t_token));
	if (!tokens)
		return (NULL);
	tokens->id = id;
	if (!handle_command_allocation(tokens, command))
		return (NULL);
	if (ft_strchr(command, '<') || ft_strchr(command, '>'))
	{
		if (!handle_redirections(tokens, command))
			return (NULL);
	}
	else
	{
		if (!handle_split(tokens, command))
			return (NULL);
	}
	tokens->prev = NULL;
	tokens->next = NULL;
	return (tokens);
}
