/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:12:11 by mmendiol          #+#    #+#             */
/*   Updated: 2025/11/02 19:08:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	lexerize_process(t_token *aux, t_env *env)
{
	int		i;
	char	**quote_divisor;
	char	*quote_joined;

	if (!aux || !aux->tokens)
		return ;
	i = -1;
	while (aux->tokens[++i])
	{
		if (!aux->tokens[i] || !*aux->tokens[i])
			continue ;
		quote_divisor = quote_command_split(aux->tokens[i]);
		if (!quote_divisor)
			continue ;
		expander(quote_divisor, env);
		quote_joined = quote_joiner(quote_divisor);
		if (quote_joined)
		{
			free(aux->tokens[i]);
			aux->tokens[i] = quote_joined;
		}
		quotes_remover(aux->tokens[i]);
		free_matrix(quote_divisor);
	}
}

void	lexerize(t_token **tokens, t_env *env)
{
	t_token	*aux;

	if (!tokens || !*tokens)
		return ;
	aux = *tokens;
	while (aux)
	{
		lexerize_process(aux, env);
		aux = aux->next;
	}
}
