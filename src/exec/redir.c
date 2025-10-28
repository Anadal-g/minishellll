/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:49:47 by anadal-g          #+#    #+#             */
/*   Updated: 2025/10/28 20:04:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int redir_command_spliter(char **r, char *str)
{
	int		i;
	int		j;
	int		commands;
	char	*word;

	i = 0;
	commands = 0;
	while (str[i])
	{
		if (process_operator_or_space(r, str, &i, &commands))
			continue ;
		j = i;
		read_till_character_redir(str, &j, &i);
		word = process_word(str, j, i);
		if (!word)
			continue ;
		r[commands++] = word;
	}
	r[commands] = NULL;
	return (1);
}

static void update_command_count(char *str, int *i, int *commands, int *in_word)
{
	int	op_len;

	op_len = is_redir(str, *i);
	if (op_len)
	{
		(*commands)++;
		*i += (op_len - 1);
		*in_word = 0;
	}
	else if (str[*i] == ' ' || str[*i] == '\t' || str[*i] == '\n')
		*in_word = 0;
	else if (!is_redir(str, *i))
	{
		if (!*in_word)
		{
			(*commands)++;
			*in_word = 1;
		}
	}
}

void conditional_operator_counter(char *str, int *i, int *commands)
{
	int	in_word;

	in_word = 0;
	while (str[++(*i)])
		update_command_count(str, i, commands, &in_word);
}

int redir_counter(char *str)
{
	int	i;
	int	commands;

	i = -1;
	commands = 0;
	conditional_operator_counter(str, &i, &commands);
	return (commands);
}

char **redir_divisor(char const *s)
{
	int		commands;
	char	**list_commands;

	if (!s)
		return (0);
	commands = redir_counter((char *)s);
	list_commands = ft_calloc(commands + 1, sizeof(char *));
	if (!list_commands)
		return (NULL);
	if (!redir_command_spliter(list_commands, (char *)s))
		return (NULL);
	return (list_commands);
}
