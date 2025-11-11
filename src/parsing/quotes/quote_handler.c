/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 20:11:05 by mmendiol          #+#    #+#             */
/*   Updated: 2025/11/11 13:17:30 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	quotes_check_in_token(char *token, int *in_quotes)
{
	int		j;
	char	quote;

	j = -1;
	quote = 0;
	while (token[++j])
	{
		if (quote_equal(token[j]) && *in_quotes == 0)
		{
			quote = token[j];
			*in_quotes = 1;
		}
		else if (*in_quotes && token[j] == quote)
		{
			*in_quotes = 0;
			quote = '\0';
		}
	}
}

int	quotes_checker(t_token *token)
{
	int	i;
	int	in_quotes;

	if (!token || !token->tokens)
		return (1);
	i = -1;
	while (token->tokens[++i])
	{
		in_quotes = 0;
		quotes_check_in_token(token->tokens[i], &in_quotes);
		if (in_quotes == 1)
			return (0);
	}
	return (1);
}

int	quotes_handler(t_token **token, char *input)
{
	t_token	*aux;

	(void)input;
	aux = *token;
	while (aux)
	{
		if (!quotes_checker(aux))
		{
			show_error(QUOTES_NOT_VALID, aux->command);
			return (0);
		}
		aux = aux->next;
	}
	return (1);
}

void	quotes_remover(char *input)
{
	char	*src;
	char	exterior_quote;

	if (!input)
		return ;
	src = input;
	exterior_quote = 0;
	while (*src)
	{
		if ((*src == DQUOTES || *src == SQUOTES) && (exterior_quote == 0
				|| exterior_quote == *src))
		{
			if (exterior_quote == 0)
				exterior_quote = *src;
			else if (exterior_quote == *src)
				exterior_quote = 0;
		}
		else
			*input++ = *src;
		src++;
	}
	*input = '\0';
}

char	*quote_joiner(char **tokens)
{
	int		final_len;
	char	*final_str;
	int		i;

	if (!tokens || !tokens[0])
		return (NULL);
	final_len = 0;
	final_str = NULL;
	i = -1;
	while (tokens[++i])
		final_len += ft_strlen(tokens[i]);
	if (final_len == 0)
	{
		final_str = ft_calloc(1, sizeof(char));
		return (final_str);
	}
	final_str = ft_calloc(final_len + 1, sizeof(char));
	if (!final_str)
		return (NULL);
	final_str[0] = '\0';
	i = -1;
	while (tokens[++i])
		ft_strcat(final_str, tokens[i]);
	return (final_str);
}
