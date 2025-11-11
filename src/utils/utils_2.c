/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 11:27:16 by anadal-g          #+#    #+#             */
/*   Updated: 2025/11/11 13:15:41 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*extract_word(char *command, int start, int end)
{
	char	*word;
	int		i;

	word = calloc(end - start + 1, sizeof(char));
	if (!word)
		exit(1);
	i = 0;
	while (start < end)
	{
		word[i] = command[start];
		i++;
		start++;
	}
	return (word);
}

static char	**add_word(char **words, char *word)
{
	size_t	words_size;
	char	**new_words;
	int		i;

	words_size = 0;
	while (words && words[words_size])
		words_size++;
	new_words = ft_calloc(words_size + 2, sizeof(char *));
	if (!new_words)
		exit(1);
	i = 0;
	while (words && words[i])
	{
		new_words[i] = words[i];
		i++;
	}
	new_words[i] = word;
	free(words);
	return (new_words);
}

int	handle_split(t_token *tokens, char *command)
{
	int		counter;
	char	*word;

	tokens->tokens = NULL;
	for (int i = 0; command && command[i]; i++)
	{
		while (command[i] == ' ')
			i++;
		counter = i + 1;
		if (command[i] == '\'' || command[i] == '\"')
		{
			jump_character(command, &counter, command[i], FALSE);
			if (command[counter] && command[counter] != ' ')
			{
				counter++;
				jump_character(command, &counter, ' ', FALSE);
			}
			word = extract_word(command, i, counter);
			tokens->tokens = add_word(tokens->tokens, word);
			i = counter - 1;
		}
		else
		{
			jump_character(command, &counter, ' ', FALSE);
			if (command[counter])
				counter--;
			word = extract_word(command, i, counter);
			tokens->tokens = add_word(tokens->tokens, word);
			i = counter - 1;
		}
	}
	if (!tokens->tokens)
	{
		free(tokens->command);
		free(tokens);
		return (0);
	}
	return (1);
}
