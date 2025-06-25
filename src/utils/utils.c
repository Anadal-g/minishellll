/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 13:18:16 by anadal-g          #+#    #+#             */
/*   Updated: 2025/06/25 13:18:44 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int character_finder(char c, char to_find)
{
	return (c == to_find);
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

char *ft_strndup(const char *s, size_t n)
{
	char *dup;
	size_t i;
	size_t len;
	
	if (!s)
		return (NULL);
		
	len = ft_strlen(s);
	if (n < len)
		len = n;
		
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
		
	i = 0;
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	
	return (dup);
}

void *ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void *new_ptr;
	size_t copy_size;
	
	if (!ptr)
		return (malloc(new_size));
		
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
		
	copy_size = old_size < new_size ? old_size : new_size;
	ft_memcpy(new_ptr, ptr, copy_size);
	free(ptr);
	
	return (new_ptr);
}

int validate_pipe_syntax(char *input)
{
	int i = 0;
	int in_quotes = 0;
	char quote_char = 0;
	
	if (!input || !*input)
		return (1);
		
	while (input[i] && (input[i] == ' ' || input[i] == '\t'))
		i++;
		
	if (input[i] == '|')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", STDERR_FILENO);
		return (0);
	}
	
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
		else if (input[i] == '|' && !in_quotes)
		{
			int j = i + 1;
			while (input[j] && (input[j] == ' ' || input[j] == '\t'))
				j++;
			if (input[j] == '|' || !input[j])
			{
				ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", STDERR_FILENO);
				return (0);
			}
		}
		i++;
	}
	
	return (1);
}