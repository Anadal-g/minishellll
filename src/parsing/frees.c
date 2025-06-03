/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:24:03 by mmendiol          #+#    #+#             */
/*   Updated: 2024/10/25 12:10:31 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_list(t_token **stack)
{
	t_token	*aux;

	while (*stack)
	{
		aux = (*stack)->next;
		free((*stack)->command);
		free_matrix((*stack)->tokens);
		free(*stack);
		*stack = aux;
	}
	*stack = NULL;
}

void	free_tokens(t_token **tokens)
{
	t_token	*current;
	t_token	*next;

	if (!tokens || !*tokens)
		return ;
	current = *tokens;
	while (current)
	{
		next = current->next;
		free(current->command);
		free_matrix(current->tokens);
		free_iofile(current->infile);
		free_iofile(current->outfile);
		free(current);
		current = next;
	}
	*tokens = NULL;
}

void	free_env(t_env **env)
{
	t_env	*current;
	t_env	*next;

	if (!env || !*env)
		return ;
	current = *env;
	while (current)
	{
		next = current->next;
		free(current->name);
		free_matrix(&current->value);
		free(current);
		current = next;
	}
	*env = NULL;
}

void	free_iofile(t_iofile *iofile)
{
	t_iofile	*tmp;

	while (iofile)
	{
		tmp = iofile;
		iofile = iofile->next;
		free(tmp->name);
		free(tmp);
	}
}
