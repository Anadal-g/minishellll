/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinamc <carolinamc@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 13:53:01 by anadal-g          #+#    #+#             */
/*   Updated: 2025/07/14 15:42:35 by carolinamc       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int validate_input_syntax(char *input)
{
	int i = 0;
	int in_quotes = 0;
	char quote_char = 0;
	if (!input || !*input)
		return (1);
	while (input[i])
	{
		if ((input[i] == '"' || input[i] == '\'') && !in_quotes)
		{
			in_quotes = 1;
			quote_char = input[i];
		}
		else if (input[i] == quote_char && in_quotes)
		{
			in_quotes = 0;
			quote_char = 0;
		}
		i++;
	}
	if (in_quotes)
	{
		ft_putstr_fd("minishell: syntax error: unclosed quotes\n", STDERR_FILENO);
		return (0);
	}
	return (1);
}

int	validate_pipe_syntax(char *input)
{
	int		i = 0;
	int		in_quotes = 0;
	char	quote_char = 0;
	if (!input || !*input)
		return (1);
	while (input[i] && (input[i] == ' ' || input[i] == '\t'))
		i++;
	if (input[i] == '|')
		return (ft_putstr_fd(
			"minishell: syntax error near unexpected token `|'\n",
			STDERR_FILENO), 0);
	while (input[i])
	{
		if ((input[i] == '"' || input[i] == '\'') && !in_quotes)
		{
			in_quotes = 1;
			quote_char = input[i];
		}
		else if (input[i] == quote_char && in_quotes)
			in_quotes = 0;
		else if (!check_pipe(input, &i, in_quotes))
			return (0);
		i++;
	}
	return (1);
}

int	check_pipe(char *input, int *i, int in_quotes)
{
	int	j;
	if (input[*i] == '|' && !in_quotes)
	{
		j = *i + 1;
		while (input[j] && (input[j] == ' ' || input[j] == '\t'))
			j++;
		if (input[j] == '|' || !input[j])
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", STDERR_FILENO);
			return (0);
		}
	}
	return (1);
}

int is_redir(char *str, int i)
{
	if (!str)
		return (0);
	if (str[i] == '<')
	{
		if (str[i + 1] == '<')
			return (2);
		return (1);
	}
	if (str[i] == '>')
	{
		if (str[i + 1] == '>')
			return (2);
		return (1);
	}
	return (0);
}

int character_finder(char c, char to_find)
{
	return (c == to_find);
}
