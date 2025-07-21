/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_stack.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinamc <carolinamc@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:02:31 by mmendiol          #+#    #+#             */
/*   Updated: 2025/07/21 16:03:40 by carolinamc       ###   ########.fr       */
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

t_token	*last_node(t_token *lst)
{
	while (lst && lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	add_node_back(t_token **stack, t_token *new)
{
	t_token	*aux;

	if (!stack || !new)
		return ;
	aux = last_node(*stack);
	if (aux)
	{
		new->prev = aux;
		new->next = NULL;
		aux->next = new;
	}
	else
		*stack = new;
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
	tokens->command = ft_strdup(command);
	if (!tokens->command)
	{
		free(tokens);
		return (NULL);
	}
	if (ft_strchr(command, '<') || ft_strchr(command, '>'))
	{
		tokens->tokens = redir_divisor(command);
		if (!tokens->tokens)
		{
			free(tokens->command);
			free(tokens);
			return (NULL);
		}
		parse_redirections(tokens);
	}
	else
	{
		tokens->tokens = ft_split(command, ' ');
		if (!tokens->tokens)
		{
			free(tokens->command);
			free(tokens);
			return (NULL);
		}
	}
	tokens->prev = NULL;
	tokens->next = NULL;
	return (tokens);
}
