/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:44:23 by mmendiol          #+#    #+#             */
/*   Updated: 2025/11/11 11:44:15 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_env_value(char *var_name, t_env *env)
{
	char	*env_value;
	t_env	*env_node;

	if (ft_strcmp(var_name, "?") == 0)
	{
		if (env)
			env_value = ft_itoa(env->last_out);
		else
			env_value = ft_itoa(0);
		if (!env_value)
			return (NULL);
	}
	else
	{
		env_node = ft_find_env(env, var_name);
		if (!env_node || !env_node->value)
			return (NULL);
		env_value = env_node->value;
	}
	return (env_value);
}

void	append_expanded(char **result, size_t *result_len, char *var_name,
		t_env *env)
{
	char	*env_value;
	size_t	env_len;

	env_value = get_env_value(var_name, env);
	if (!env_value)
		return ;
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

void	append_other_characters(char **result, size_t *result_len, char c)
{
	*result = ft_realloc(*result, *result_len, *result_len + 2);
	if (result)
	{
		(*result)[*result_len] = c;
		(*result)[*result_len + 1] = '\0';
		(*result_len)++;
	}
}

char	*expand_variable(char *str, t_env *env)
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

void	expander(char **tokens, t_env *env)
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
