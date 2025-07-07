/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_creator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/07/07 12:26:39 by anadal-g         ###   ########.fr       */
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

static void create_minimal_env(t_env **env_list)
{
	t_env *new_env;
	char *pwd;
	
	// Create PWD
	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		new_env = ft_calloc(1, sizeof(t_env));
		if (new_env)
		{
			new_env->name = ft_strdup("PWD");
			new_env->value = pwd;
			new_env->last_out = 0;
			ft_addback_env(env_list, new_env);
		}
		else
			free(pwd);
	}
	
	// Create SHLVL=1
	new_env = ft_calloc(1, sizeof(t_env));
	if (new_env)
	{
		new_env->name = ft_strdup("SHLVL");
		new_env->value = ft_strdup("1");
		new_env->last_out = 0;
		ft_addback_env(env_list, new_env);
	}
	
	// Create _=/usr/bin/env (this is what bash sets when started with env -i)
	new_env = ft_calloc(1, sizeof(t_env));
	if (new_env)
	{
		new_env->name = ft_strdup("_");
		new_env->value = ft_strdup("/usr/bin/env");
		new_env->last_out = 0;
		ft_addback_env(env_list, new_env);
	}
}

void ft_init_env(t_env **env_list, char **env)
{
	int		i;
	t_env	*new_env;

	if (!env_list)
		return;
		
	i = 0;
	while (env && env[i])
	{
		new_env = ft_create_env_node(env[i]);
		if (new_env)
			ft_addback_env(env_list, new_env);
		i++;
	}
	
	// If no environment was provided (env -i case), create minimal environment
	if (!*env_list)
	{
		create_minimal_env(env_list);
	}
	else
	{
		// Ensure SHLVL is properly incremented
		t_env *shlvl_var = ft_find_env(*env_list, "SHLVL");
		if (shlvl_var && shlvl_var->value)
		{
			int current_shlvl = ft_atoi(shlvl_var->value);
			free(shlvl_var->value);
			shlvl_var->value = ft_itoa(current_shlvl + 1);
		}
		else if (!shlvl_var)
		{
			// Create SHLVL if it doesn't exist
			new_env = ft_calloc(1, sizeof(t_env));
			if (new_env)
			{
				new_env->name = ft_strdup("SHLVL");
				new_env->value = ft_strdup("1");
				new_env->last_out = 0;
				ft_addback_env(env_list, new_env);
			}
		}
	}
}
