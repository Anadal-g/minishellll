/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 19:00:00 by anadal-g          #+#    #+#             */
/*   Updated: 2025/11/12 10:41:16 by anadal-g         ###   ########.fr       */
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

static void	add_token_node(t_token **stack, char *content)
{
	t_token	*node;
	t_token	*last;

	if (!*stack)
		node = create_node(1, content);
	else
	{
		last = last_node(*stack);
		node = create_node(last->id + 1, content);
	}
	if (node)
		add_node_back(stack, node);
}

void	add_node_tokens(t_token **stack_tokens, char **splited_tokens)
{
	int	i;

	if (!stack_tokens || !splited_tokens)
		return ;
	i = 0;
	while (splited_tokens[i])
	{
		add_token_node(stack_tokens, splited_tokens[i]);
		i++;
	}
}

static int	validate_tokens_splited(char **tokens_splited)
{
	int	i;

	i = 0;
	while (tokens_splited[i])
	{
		if (!validate_command_not_empty(tokens_splited[i]))
		{
			ft_putstr_fd("minishell: error: empty command\n", STDERR_FILENO);
			free_matrix(tokens_splited);
			return (0);
		}
		i++;
	}
	return (1);
}

void	create_tokens(char *input, t_token **tokens)
{
	char	**splitted;
	char	*trimmed;

	if (!input || !tokens)
	{
		if (tokens)
			ft_putstr_fd("Error\n", STDERR_FILENO);
		return ;
	}
	trimmed = ft_strtrim(input, " \t\n");
	if (!trimmed || !*trimmed)
		return (free(trimmed));
	free(trimmed);
	splitted = command_spliter(input, PIPE);
	if (!splitted)
		return ;
	if (!validate_tokens_splited(splitted))
		return ;
	add_node_tokens(tokens, splitted);
	free_matrix(splitted);
}
