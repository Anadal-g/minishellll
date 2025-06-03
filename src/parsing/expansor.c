/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:44:23 by mmendiol          #+#    #+#             */
/*   Updated: 2024/10/03 17:39:45 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_variable_name(char **str)
{
	char	*var_start;
	size_t	len;

	var_start = *str;
	len = 0;
	while (**str && (isalnum(**str) || **str == '_'))
		(*str)++;
	len = *str - var_start;
	return (ft_strndup(var_start, len));
}

void	append_expanded(char **result, size_t *result_len, char *var_name)
{
	char	*env_value;
	size_t	env_len;

	env_value = getenv(var_name);
	env_len = ft_strlen(env_value);
	if (env_value)
	{
		*result = ft_realloc(*result, *result_len, *result_len + env_len + 1);
		if (*result)
		{
			ft_strcat(*result, env_value);
			*result_len += env_len;
		}
	}
}

void	append_other_characters(char **result, size_t *result_len, char c)
{
	size_t	len;

	*result = ft_realloc(*result, *result_len, *result_len + 2);
	if (*result)
	{
		len = ft_strlen(*result);
		(*result)[len] = c;
		(*result)[len + 1] = '\0';
		(*result_len)++;
	}
}

char	*expand_variable(char *str)
{
	char	*result;
	size_t	result_len;
	char	*var_name;

	result_len = 0;
	result = ft_calloc(1, sizeof(char));
	if (!result)
		return (free(result), NULL);
	result[0] = '\0';
	while (*str)
	{
		if (*str == '$')
		{
			str++;
			var_name = get_variable_name(&str);
			if (var_name)
			{
				append_expanded(&result, &result_len, var_name);
				free(var_name);
			}
		}
		else
			append_other_characters(&result, &result_len, *str++);
	}
	return (result);
}

void	expander(char **tokens)
{
	int		i;
	char	*expanded;

	i = -1;
	while (tokens[++i])
	{
		if (tokens[i][0] != '\'')
		{
			expanded = expand_variable(tokens[i]);
			if (expanded)
			{
				free(tokens[i]);
				tokens[i] = expanded;
			}
		}
	}
}
