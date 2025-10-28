/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:49:47 by anadal-g          #+#    #+#             */
/*   Updated: 2025/10/28 20:03:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void read_till_character_redir(char *input, int *start, int *counter)
{
	if (!input || !start || !counter)
		return ;
	*counter = *start;
	while (input[*counter])
	{
		if (input[*counter] == '<' || input[*counter] == '>')
			break ;
		(*counter)++;
	}
}

int process_operator_or_space(char **r, char *str, int *i, int *commands)
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

char *process_word(char *str, int j, int i)
{
	char *tmp_substr;
	char *tmp_trim;

	tmp_substr = ft_substr(str, j, i - j);
	if (!tmp_substr || !*tmp_substr)
	{
		free(tmp_substr);
		return (NULL);
	}
	tmp_trim = ft_strtrim(tmp_substr, " ");
	free(tmp_substr);
	return (tmp_trim);
}