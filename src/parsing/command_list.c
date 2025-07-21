/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinamc <carolinamc@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 19:39:07 by mmendiol          #+#    #+#             */
/*   Updated: 2025/07/21 13:18:36 by carolinamc       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	validate_command_not_empty(char *command)
{
	char	*trimmed;
	int		result;

	if (!command)
		return (0);
	trimmed = ft_strtrim(command, " \t");
	if (!trimmed || !*trimmed)
	{
		if (trimmed)
			free(trimmed);
		return (0);
	}
	result = 1;
	free(trimmed);
	return (result);
}

void	add_node_tokens(t_token **stack_tokens, char **splited_tokens)
{
	int		i;
	t_token	*node;
	t_token	*node_last;

	if (!stack_tokens || !splited_tokens)
		return ;
	i = -1;
	while (splited_tokens[++i])
	{
		if (!*stack_tokens)
			node = create_node(1, splited_tokens[i]);
		else
		{
			node_last = last_node(*stack_tokens);
			node = create_node(node_last->id + 1, splited_tokens[i]);
		}
		if (node)
			add_node_back(stack_tokens, node);
	}
}

void	create_tokens(char *input, t_token **tokens)
{
	char	**tokens_splited;
	char	*trimmed;
	int		i;

	if (!input || !tokens)
	{
		if (tokens)
			ft_putstr_fd("Error\n", STDERR_FILENO);
		return ;
	}
	trimmed = ft_strtrim(input, " \t\n");
	if (!trimmed || !*trimmed)
	{
		if (trimmed)
			free(trimmed);
		return ;
	}
	free(trimmed);
	tokens_splited = command_spliter(input, PIPE);
	if (!tokens_splited)
		return ;
	i = 0;
	while (tokens_splited[i])
	{
		if (!validate_command_not_empty(tokens_splited[i]))
		{
			ft_putstr_fd("minishell:error: empty command\n", STDERR_FILENO);
			free_matrix(tokens_splited);
			return ;
		}
		i++;
	}
	add_node_tokens(tokens, tokens_splited);
	free_matrix(tokens_splited);
}
