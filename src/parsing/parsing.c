/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:08:26 by anadal-g          #+#    #+#             */
/*   Updated: 2025/11/12 10:51:46 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	write_command(char **r, char *str, char c)
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

char	**command_spliter(char const *s, char c)
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

static int	handle_quotes_and_count(char *str, int *i, int *in_word,
		int *commands)
{
	char	quote;

	quote = str[(*i)++];
	jump_character(str, i, quote, FALSE);
	if (!(*in_word))
	{
		(*commands)++;
		(*in_word) = 1;
	}
	return (1);
}

static int	handle_normal_char(char ch, char c, int *in_word, int *commands)
{
	if (character_finder(ch, c))
	{
		*in_word = 0;
		return (1);
	}
	else if (ch != ' ' && ch != '\t')
	{
		if (!(*in_word))
		{
			(*commands)++;
			(*in_word) = 1;
		}
	}
	return (0);
}

int	command_counter(char *str, char c)
{
	int	i;
	int	commands;
	int	in_word;

	i = -1;
	commands = 0;
	in_word = 0;
	while (str[++i])
	{
		if (str[i] && (str[i] == DQUOTES || str[i] == SQUOTES))
		{
			handle_quotes_and_count(str, &i, &in_word, &commands);
			if (!str[i])
				break ;
		}
		else
			handle_normal_char(str[i], c, &in_word, &commands);
	}
	return (commands);
}
