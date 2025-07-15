/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinamc <carolinamc@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 13:53:01 by anadal-g          #+#    #+#             */
/*   Updated: 2025/07/15 13:07:36 by carolinamc       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_quote_state(char current_char, int *in_quotes, char *quote_char)
{
	if ((current_char == '"' || current_char == '\'') && !(*in_quotes))
	{
		*in_quotes = 1;
		*quote_char = current_char;
	}
	else if (current_char == *quote_char && *in_quotes)
	{
		*in_quotes = 0;
		*quote_char = 0;
	}
}

int	validate_input_syntax(char *input)
{
	int		i;
	int		in_quotes;
	char	quote_char;

	if (!input || !*input)
		return (1);
	i = 0;
	in_quotes = 0;
	quote_char = 0;
	while (input[i])
	{
		handle_quote_state(input[i], &in_quotes, &quote_char);
		i++;
	}
	if (in_quotes)
	{
		ft_putstr_fd("minishell:syntax error:unclosed quotes\n", STDERR_FILENO);
		return (0);
	}
	return (1);
}

int	validate_initial_pipe(char *input)
{
	int	i;

	i = 0;
	if (!input || !*input)
		return (1);
	while (input[i] && (input[i] == ' ' || input[i] == '\t'))
		i++;
	if (input[i] == '|')
	{
		ft_putstr_fd("minishell: unexpected token `|'\n", STDERR_FILENO);
		return (0);
	}
	return (i);
}

int	validate_pipe_syntax(char *input)
{
	int		i;
	int		in_quotes;
	char	quote_char;

	in_quotes = 0;
	quote_char = 0;
	i = validate_initial_pipe(input);
	if (i <= 0)
	{
		if (i == 0)
			return (0);
		return (1);
	}
	while (input[i])
	{
		handle_quote_state(input[i], &in_quotes, &quote_char);
		if (!check_pipe_sequence(input, &i, in_quotes))
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
			ft_putstr_fd("minishell: unexpected token `|'\n", STDERR_FILENO);
			return (0);
		}
	}
	return (1);
}
