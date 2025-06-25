/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:08:26 by anadal-g          #+#    #+#             */
/*   Updated: 2025/06/25 13:28:50 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void jump_character(char *str, int *counter, char c, int flag)
{
	if (flag == TRUE)
	{
		while (str[*counter] && str[*counter] == c)
			(*counter)++;
	}
	else
	{
		while (str[*counter] && str[*counter] != c)
			(*counter)++;
		if (str[*counter] == c)
			(*counter)++;
	}
}

void read_till_character(char *input, int *start, int *counter, char c)
{
	char	quote;

	*start = *counter;
	while (input[*counter])
	{
		if (input[*counter] == DQUOTES || input[*counter] == SQUOTES)
		{
			quote = input[(*counter)++];
			jump_character(input, counter, quote, FALSE);
		}
		else if (character_finder(input[*counter], c))
			break ;
		(*counter)++;
	}
}

int write_command(char **r, char *str, char c)
{
	int		i;
	int		j;
	int		comands;
	char	*tmp_substr;
	char	*tmp_trim;

	i = 0;
	comands = 0;
	while (str[i])
	{
		jump_character(str, &i, c, TRUE);
		if (str[i] == '\0')
			break ;
		read_till_character(str, &j, &i, c);
		tmp_substr = ft_substr(str, j, i - j);
		if (tmp_substr == NULL)
			return (free_matrix_bool(r));
		tmp_trim = ft_strtrim(tmp_substr, " ");
		free(tmp_substr);
		if (tmp_trim == NULL)
			return (free_matrix_bool(r));
		r[comands] = tmp_trim;
		comands++;
	}
	return (1);
}

int command_counter(char *str, char c)
{
	int i = -1;
	int commands = 0;
	char quote;
	int in_word = 0;

	while (str[++i])
	{
		if (str[i] && (str[i] == DQUOTES || str[i] == SQUOTES))
		{
			quote = str[i++];
			jump_character(str, &i, quote, FALSE);
			if (!in_word)
			{
				commands++;
				in_word = 1;
			}
		}
		else if (character_finder(str[i], c))
		{
			in_word = 0;
		}
		else if (!character_finder(str[i], c) && str[i] != ' ' && str[i] != '\t')
		{
			if (!in_word)
			{
				commands++;
				in_word = 1;
			}
		}
	}
	return (commands);
}

char **command_spliter(char const *s, char c)
{
	int		commands;
	char	**list_commands;

	if (!s)
		return (0);
	commands = command_counter((char *)s, c);
	list_commands = ft_calloc(commands + 1, sizeof(char *));
	if (!list_commands)
		return (NULL);
	if (!write_command(list_commands, (char *)s, c))
		return (NULL);
	return (list_commands);
}