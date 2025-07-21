/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinamc <carolinamc@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 20:11:05 by mmendiol          #+#    #+#             */
/*   Updated: 2025/07/21 13:14:44 by carolinamc       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	quote_equal(char c)
{
	return (c == DQUOTES || c == SQUOTES);
}

static void	extract_token(char *str, int *i, int *j, char **tokens)
{
	int		start;
	char	quote;

	start = *i;
	while (str[*i])
	{
		if (quote_equal(str[*i]))
		{
			quote = str[(*i)++];
			while (str[*i] && str[*i] != quote)
				(*i)++;
			if (str[*i] == quote)
				(*i)++;
		}
		else if (str[*i] == ' ' || str[*i] == '\t')
			break ;
		else
			(*i)++;
	}
	tokens[*j] = ft_strndup(&str[start], *i - start);
	(*j)++;
}

static int	skip_command(char *str, int i)
{
	char	quote;

	while (str[i] && str[i] != ' ' && str[i] != '\t')
	{
		if (quote_equal(str[i]))
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				i++;
			if (str[i])
				i++;
		}
		else
			i++;
	}
	return (i);
}

static int	quote_command_counter(char *str)
{
	int		i;
	int		commands;

	i = 0;
	commands = 0;
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (!str[i])
			break ;
		commands++;
		i = skip_command(str, i);
	}
	return (commands);
}

char	**quote_command_split(char *str)
{
	int		i;
	int		j;
	int		num_tokens;
	char	**tokens;

	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	num_tokens = quote_command_counter(str);
	tokens = ft_calloc((num_tokens + 1), sizeof(char *));
	if (!tokens)
		return (NULL);
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
		if (!str[i])
			break ;
		extract_token(str, &i, &j, tokens);
	}
	tokens[j] = NULL;
	return (tokens);
}
