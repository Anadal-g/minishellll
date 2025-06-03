/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 19:39:07 by mmendiol          #+#    #+#             */
/*   Updated: 2025/06/03 12:24:26 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


int validate_command_not_empty(char *command)
{
    char *trimmed;
    int result;
    
    if (!command)
        return (0);
    
    trimmed = ft_strtrim(command, " \t");
    if (!trimmed || !*trimmed)
    {
        free(trimmed);
        return (0);
    }
    
    result = 1;
    free(trimmed);
    return (result);
}

int validate_tokens_not_empty(char **splited_tokens)
{
    int i = 0;
    
    if (!splited_tokens)
        return (0);
    while (splited_tokens[i])
    {
        char *trimmed = ft_strtrim(splited_tokens[i], " \t");
        if (!trimmed || !*trimmed)
        {
            free(trimmed);
            ft_putstr_fd("minishell: syntax error: empty command\n", STDERR_FILENO);
            return (0);
        }
        free(trimmed);
        i++;
    }
    return (1);
}

void	add_node_tokens(t_token **stack_tokens, char **splited_tokens)
{
	int		i;
	t_token	*node;
	t_token	*node_last;

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
		add_node_back(stack_tokens, node);
	}
}

void create_tokens(char *input, t_token **tokens)
{
    char **tokens_splited;
    int i;

    if (input != NULL)
    {
        tokens_splited = command_spliter(input, PIPE);
        if (!tokens_splited)
            return;
        i = 0;
        while (tokens_splited[i])
        {
            if (!validate_command_not_empty(tokens_splited[i]))
            {
                ft_putstr_fd("minishell: syntax error: empty command\n", STDERR_FILENO);
                free_matrix(tokens_splited);
                return;
            }
            i++;
        }
        add_node_tokens(tokens, tokens_splited);
        free_matrix(tokens_splited);
    }
    else
        ft_putstr_fd("Error\n", STDERR_FILENO);
}