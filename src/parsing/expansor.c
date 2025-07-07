/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:44:23 by mmendiol          #+#    #+#             */
/*   Updated: 2025/07/04 13:01:56 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *get_variable_name(char **str)
{
	char	*var_start;
	size_t	len;

	if (!str || !*str)
		return (NULL);
		
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
	
	if (len == 0)
		return (NULL);
		
	return (ft_strndup(var_start, len));
}

void append_expanded(char **result, size_t *result_len, char *var_name, t_env *env)
{
	char	*env_value;
	size_t	env_len;
	t_env	*env_node;
	char	*new_result;

	if (!result || !*result || !result_len || !var_name)
		return;

	env_value = NULL;
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
	if (env_len == 0)
	{
		if (ft_strcmp(var_name, "?") == 0)
			free(env_value);
		return;
	}
	
	new_result = ft_realloc(*result, *result_len, *result_len + env_len + 1);
	if (!new_result)
	{
		if (ft_strcmp(var_name, "?") == 0)
			free(env_value);
		return;
	}
	
	*result = new_result;
	ft_strcat(*result, env_value);
	*result_len += env_len;
	
	if (ft_strcmp(var_name, "?") == 0)
		free(env_value);
}

void append_other_characters(char **result, size_t *result_len, char c)
{
	char	*new_result;
	size_t	len;

	if (!result || !*result || !result_len)
		return;

	new_result = ft_realloc(*result, *result_len, *result_len + 2);
	if (!new_result)
		return;
		
	*result = new_result;
	len = ft_strlen(*result);
	(*result)[len] = c;
	(*result)[len + 1] = '\0';
	(*result_len)++;
}

char *expand_variable(char *str, t_env *env)
{
	char	*result;
	size_t	result_len;
	char	*var_name;

	if (!str)
		return (NULL);

	result_len = 1;
	result = ft_calloc(1, sizeof(char));
	if (!result)
		return (NULL);
	
	while (*str)
	{
		if (*str == '$' && *(str + 1) && *(str + 1) != ' ' && *(str + 1) != '\t')
		{
			str++;
			var_name = get_variable_name(&str);
			if (var_name)
			{
				append_expanded(&result, &result_len, var_name, env);
				free(var_name);
				if (!result)
					return (NULL);
			}
		}
		else
		{
			append_other_characters(&result, &result_len, *str);
			if (!result)
				return (NULL);
			str++;
		}
	}
	return (result);
}

void expander(char **tokens, t_env *env)
{
	int		i;
	char	*expanded;

	if (!tokens)
		return;

	i = 0;
	while (tokens[i])
	{
		if (tokens[i] && tokens[i][0] && tokens[i][0] != '\'')
		{
			expanded = expand_variable(tokens[i], env);
			if (expanded)
			{
				free(tokens[i]);
				tokens[i] = expanded;
			}
		}
		i++;
	}
}
