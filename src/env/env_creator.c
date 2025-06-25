/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_creator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:15:04 by anadal-g          #+#    #+#             */
/*   Updated: 2025/06/25 13:49:03 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env *ft_create_env_node(char *env_var)
{
	t_env	*new_node;
	char	*equal_sign;

	new_node = ft_calloc(1, sizeof(t_env));
	if (!new_node)
		return (NULL);
	equal_sign = ft_strchr(env_var, '=');
	if (!equal_sign)
	{
		new_node->name = ft_strdup(env_var);
		new_node->value = NULL;
	}
	else
	{
		new_node->name = ft_substr(env_var, 0, equal_sign - env_var);
		new_node->value = ft_strdup(equal_sign + 1);
	}
	new_node->prev = NULL;
	new_node->next = NULL;
	new_node->last_out = 0;
	return (new_node);
}

void ft_init_env(t_env **env_list, char **env)
{
	int		i;
	t_env	*new_env;

	i = 0;
	while (env && env[i])
	{
		new_env = ft_create_env_node(env[i]);
		if (new_env)
			ft_addback_env(env_list, new_env);
		i++;
	}
	
	// Ensure we have a basic environment
	if (!*env_list)
	{
		new_env = ft_calloc(1, sizeof(t_env));
		if (new_env)
		{
			new_env->name = ft_strdup("PWD");
			new_env->value = getcwd(NULL, 0);
			new_env->last_out = 0;
			*env_list = new_env;
		}
	}
}