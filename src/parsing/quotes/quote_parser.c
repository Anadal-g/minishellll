/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 20:11:05 by mmendiol          #+#    #+#             */
/*   Updated: 2025/06/03 12:19:38 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	quote_equal(char c)
{
	return (c == DQUOTES || c == SQUOTES);
}

void	conditional_quote_counter(char *str, int *i, int *commands)
{
	char	quote;
	int		in_quotes;

	quote = 0;
	in_quotes = 0;
	while (str[++(*i)])
	{
		if (quote_equal(str[*i]))
		{
			quote = str[(*i)++];
			jump_character(str, i, quote, FALSE);
			(*commands)++;
			in_quotes = 0;
		}
		else if (!quote_equal(str[*i]))
		{
			if (!in_quotes)
			{
				(*commands)++;
				in_quotes = 1;
			}
		}
		else
			in_quotes = 0;
	}
}

int	quote_command_counter(char *str)
{
	int	i;
	int	commands;

	i = -1;
	commands = 0;
	conditional_quote_counter(str, &i, &commands);
	return (commands);
}

void extract_token(char *str, int *i, int *j, char **tokens)
{
    int start;
    char quote;

    start = *i;
    
    while (str[*i])
    {
        if (quote_equal(str[*i]))
        {
            quote = str[(*i)++];
            while (str[*i] && str[*i] != quote)
                (*i)++;
            if (str[*i] == quote)
                (*i)++; // Saltar la comilla de cierre
        }
        else if (str[*i] == ' ' || str[*i] == '\t')
            break; // Fin del token
        else
            (*i)++; // Carácter normal
    }
    
    tokens[*j] = ft_strndup(&str[start], *i - start);
    (*j)++;
}

char	**quote_command_split(char *str)
{
	int		i;
	int		j;
	int		num_tokens;
	char	**tokens;

	i = 0;
	j = 0;
	num_tokens = quote_command_counter(str);
	tokens = ft_calloc((num_tokens + 1), sizeof(char *));
	if (!tokens)
		return (NULL);
	while (str[i])
		extract_token(str, &i, &j, tokens);
	tokens[j] = NULL;
	return (tokens);
}
