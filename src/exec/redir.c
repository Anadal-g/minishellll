/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinamc <carolinamc@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:49:47 by anadal-g          #+#    #+#             */
/*   Updated: 2025/07/22 14:03:26 by carolinamc       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	process_operator_or_space(char **r, char *str, int *i, int *commands)
{
	int	op_len;

	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t' || str[*i] == '\n'))
		(*i)++;
	if (str[*i] == '\0')
		return (0);
	op_len = is_redir(str, *i);
	if (op_len)
	{
		r[(*commands)++] = ft_substr(str, *i, op_len);
		*i += op_len;
		return (1);
	}
	return (0);
}

int	redir_command_spliter(char **r, char *str)
{
	int		i;
	int		j;
	int		commands;
	char	*tmp_substr;

	i = 0;
	commands = 0;
	while (str[i])
	{
		if (process_operator_or_space(r, str, &i, &commands))
			continue ;
		j = i;
		read_till_character_redir(str, &j, &i);
		tmp_substr = ft_substr(str, j, i - j);
		if (!tmp_substr || !*tmp_substr)
		{
			free(tmp_substr);
			continue ;
		}
		if (!handle_trim_and_store(tmp_substr, &r[commands++]))
			return (0);
	}
	r[commands] = NULL;
	return (1);
}

void	conditional_operator_counter(char *str, int *i, int *commands)
{
	int	op_len;
	int	in_word;

	in_word = 0;
	while (str[++(*i)])
	{
		op_len = is_redir(str, *i);
		if (op_len)
		{
			(*commands)++;
			*i += (op_len - 1);
			in_word = 0;
		}
		else if (str[*i] == ' ' || str[*i] == '\t' || str[*i] == '\n')
			in_word = 0;
		else if (!is_redir(str, *i))
		{
			if (!in_word)
			{
				(*commands)++;
				in_word = 1;
			}
		}
	}
}

int	redir_counter(char *str)
{
	int	i;
	int	commands;

	i = -1;
	commands = 0;
	conditional_operator_counter(str, &i, &commands);
	return (commands);
}

char	**redir_divisor(char const *s)
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
