/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 11:27:16 by anadal-g          #+#    #+#             */
/*   Updated: 2025/11/12 10:35:58 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*extract_word(char *command, int start, int end)
{
	char	*word;
	int		i;

	word = ft_calloc(end - start + 1, sizeof(char));
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
	size_t	size;
	char	**new_words;
	int		i;

	size = 0;
	while (words && words[size])
		size++;
	new_words = ft_calloc(size + 2, sizeof(char *));
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

static int	process_quoted_word(t_token *tokens, char *cmd, int *i)
{
	int		counter;
	char	*word;

	counter = *i + 1;
	jump_character(cmd, &counter, cmd[*i], FALSE);
	if (cmd[counter] && cmd[counter] != ' ')
	{
		counter++;
		jump_character(cmd, &counter, ' ', FALSE);
	}
	word = extract_word(cmd, *i, counter);
	tokens->tokens = add_word(tokens->tokens, word);
	*i = counter - 1;
	return (0);
}

static int	process_normal_word(t_token *tokens, char *cmd, int *i)
{
	int		counter;
	char	*word;

	counter = *i + 1;
	jump_character(cmd, &counter, ' ', FALSE);
	if (cmd[counter])
		counter--;
	word = extract_word(cmd, *i, counter);
	tokens->tokens = add_word(tokens->tokens, word);
	*i = counter - 1;
	return (0);
}

int	handle_split(t_token *tokens, char *cmd)
{
	int	i;

	i = 0;
	tokens->tokens = NULL;
	while (cmd && cmd[i])
	{
		while (cmd[i] == ' ')
			i++;
		if (!cmd[i])
			break ;
		if (cmd[i] == '\'' || cmd[i] == '\"')
			process_quoted_word(tokens, cmd, &i);
		else
			process_normal_word(tokens, cmd, &i);
		i++;
	}
	if (!tokens->tokens)
	{
		free(tokens->command);
		free(tokens);
		return (0);
	}
	return (1);
}
