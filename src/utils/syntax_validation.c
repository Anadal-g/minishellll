/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 13:53:01 by anadal-g          #+#    #+#             */
/*   Updated: 2025/06/25 13:53:03 by anadal-g         ###   ########.fr       */
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
