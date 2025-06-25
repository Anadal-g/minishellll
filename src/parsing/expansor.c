/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:44:23 by mmendiol          #+#    #+#             */
/*   Updated: 2025/06/25 13:28:36 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *get_variable_name(char **str)
{
	char	*var_start;
	size_t	len;

	var_start = *str;
	len = 0;
	
	if (**str == '?')
	{
		(*str)++;
		return (ft_strdup("?"));
	}
	
	while (**str && (ft_isalnum(**str) || **str == '_'))
		(*str)++;
	len = *str - var_start;
	return (ft_strndup(var_start, len));
}

void append_expanded(char **result, size_t *result_len, char *var_name, t_env *env)
{
	char	*env_value;
	size_t	env_len;
	t_env	*env_node;

	if (ft_strcmp(var_name, "?") == 0)
	{
		env_value = ft_itoa(env ? env->last_out : 0);
		if (!env_value)
			return;
	}
	else
	{
		env_node = ft_find_env(env, var_name);
		if (!env_node || !env_node->value)
			return;
		env_value = env_node->value;
	}
	
	env_len = ft_strlen(env_value);
	*result = ft_realloc(*result, *result_len, *result_len + env_len + 1);
	if (*result)
	{
		ft_strcat(*result, env_value);
		*result_len += env_len;
	}
	
	if (ft_strcmp(var_name, "?") == 0)
		free(env_value);
}

void append_other_characters(char **result, size_t *result_len, char c)
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

char *expand_variable(char *str, t_env *env)
{
	char	*result;
	size_t	result_len;
	char	*var_name;

	result_len = 0;
	result = ft_calloc(1, sizeof(char));
	if (!result)
		return (NULL);
	result[0] = '\0';
	
	while (*str)
	{
		if (*str == '$' && *(str + 1))
		{
			str++;
			var_name = get_variable_name(&str);
			if (var_name)
			{
				append_expanded(&result, &result_len, var_name, env);
				free(var_name);
			}
		}
		else
			append_other_characters(&result, &result_len, *str++);
	}
	return (result);
}

void expander(char **tokens, t_env *env)
{
	int		i;
	char	*expanded;

	i = -1;
	while (tokens[++i])
	{
		if (tokens[i][0] != '\'')
		{
			expanded = expand_variable(tokens[i], env);
			if (expanded)
			{
				free(tokens[i]);
				tokens[i] = expanded;
			}
		}
	}
}