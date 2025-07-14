/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinamc <carolinamc@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:15:04 by anadal-g          #+#    #+#             */
/*   Updated: 2025/07/14 13:27:30 by carolinamc       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ft_init_env(t_env **env_list, char **env) // Ensure we have a basic environment
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

char	**env_to_array(t_env *env)
{
	int		count = 0;
	t_env	*tmp = env;
	char	**env_array;
	while (tmp)
	{
		if (tmp->value)
			count++;
		tmp = tmp->next;
	}
	env_array = malloc(sizeof(char *) * (count + 1));
	if (!env_array)
		return (NULL);
	if (!fill_env_array(env, env_array))
	{
		free_matrix(env_array);
		return (NULL);
	}
	return (env_array);
}

int	fill_env_array(t_env *env, char **env_array)
{
	int		i = 0;
	char	*var;
	while (env)
	{
		if (env->value)
		{
			var = ft_strjoin(env->name, "=");
			if (!var)
				return (0);
			env_array[i] = ft_strjoin(var, env->value);
			free(var);
			if (!env_array[i])
				return (0);
			i++;
		}
		env = env->next;
	}
	env_array[i] = NULL;
	return (1);
}

void set_shell_lvl(t_env **envp)
{
	t_env	*data = ft_find_env(*envp, "SHLVL");
	int		nb;
	char	*aux;
	if (data && data->value)
	{
		nb = ft_atoi(data->value);
		aux = ft_itoa(nb + 1);
		if (aux == NULL)
		{
			perror("Error al asignar memoria para SHLVL");
			return;
		}
		free(data->value);
		data->value = aux;
	}
	else
	{
		data = ft_new_env("SHLVL", "1");
		if (!data)
		{
			perror("Memory Error");
			return;
		}
		ft_addback_env(envp, data);
	}
}
