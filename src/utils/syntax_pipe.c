/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 13:53:01 by anadal-g          #+#    #+#             */
/*   Updated: 2025/10/28 20:29:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	process_pipe_syntax_loop(char *input, int *i_ptr,
		int *in_quotes_ptr, char *quote_char_ptr)
{
	int	j;

	while (input[*i_ptr])
	{
		handle_quote_state(input[*i_ptr], in_quotes_ptr, quote_char_ptr);
		if (input[*i_ptr] == '|' && !(*in_quotes_ptr))
		{
			j = *i_ptr + 1;
			while (input[j] && (input[j] == ' ' || input[j] == '\t'))
			{
				j++;
			}
			if (input[j] == '|' || !input[j])
			{
				ft_putstr_fd("minishell:unexpected token`|'\n", STDERR_FILENO);
				return (0);
			}
		}
		(*i_ptr)++;
	}
	return (1);
}

static void	process_quote_state_loop(char *input, int *i_ptr,
		int *in_quotes_ptr, char *quote_char_ptr)
{
	while (input[*i_ptr])
	{
		if ((input[*i_ptr] == '"' || input[*i_ptr] == '\'')
			&& !(*in_quotes_ptr))
		{
			*in_quotes_ptr = 1;
			*quote_char_ptr = input[*i_ptr];
		}
		else if (input[*i_ptr] == *quote_char_ptr && *in_quotes_ptr)
		{
			*in_quotes_ptr = 0;
			*quote_char_ptr = 0;
		}
		(*i_ptr)++;
	}
}

int	validate_input_syntax(char *input)
{
	int		i;
	int		in_quotes;
	char	quote_char;

	i = 0;
	in_quotes = 0;
	quote_char = 0;
	if (!input || !*input)
	{
		return (1);
	}
	process_quote_state_loop(input, &i, &in_quotes, &quote_char);
	if (in_quotes)
	{
		ft_putstr_fd("minishell:syntax error:unclosed quotes\n", STDERR_FILENO);
		return (0);
	}
	return (1);
}

int	validate_pipe_syntax(char *input)
{
	int		i;
	int		in_quotes;
	char	quote_char;
	int		result;

	i = 0;
	in_quotes = 0;
	quote_char = 0;
	if (!input || !*input)
	{
		return (1);
	}
	while (input[i] && (input[i] == ' ' || input[i] == '\t'))
	{
		i++;
	}
	if (input[i] == '|')
	{
		ft_putstr_fd("minishell: unexpected token `|'\n", STDERR_FILENO);
		return (0);
	}
	result = process_pipe_syntax_loop(input, &i, &in_quotes, &quote_char);
	return (result);
}

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
