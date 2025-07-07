/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 16:59:23 by anadal-g          #+#    #+#             */
/*   Updated: 2025/07/04 13:18:13 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int count_env_vars(t_env *env)
{
	int count;
	t_env *current;
	
	count = 0;
	current = env;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

static t_env **create_env_array(t_env *env, int count)
{
	t_env **array;
	t_env *current;
	int i;
	
	array = malloc(sizeof(t_env *) * count);
	if (!array)
		return (NULL);
	
	current = env;
	i = 0;
	while (current && i < count)
	{
		array[i] = current;
		current = current->next;
		i++;
	}
	return (array);
}

static int compare_env_names(const void *a, const void *b)
{
	t_env *env_a;
	t_env *env_b;
	
	env_a = *(t_env **)a;
	env_b = *(t_env **)b;
	
	return (ft_strcmp(env_a->name, env_b->name));
}

static void print_export_env(t_env *env)
{
	t_env **env_array;
	int count;
	int i;
	
	if (!env)
		return;
		
	count = count_env_vars(env);
	if (count == 0)
		return;
		
	env_array = create_env_array(env, count);
	if (!env_array)
		return;
	
	qsort(env_array, count, sizeof(t_env *), compare_env_names);
	
	i = 0;
	while (i < count)
	{
		printf("declare -x %s", env_array[i]->name);
		if (env_array[i]->value)
			printf("=\"%s\"", env_array[i]->value);
		printf("\n");
		i++;
	}
	
	free(env_array);
}

static int is_valid_identifier(char *str)
{
	int i;
	
	if (!str || !*str)
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int export_variable(char *arg, t_env **env)
{
	char *equal_pos;
	char *name;
	char *value;
	t_env *existing;
	t_env *new_env;
	
	equal_pos = ft_strchr(arg, '=');
	if (equal_pos)
	{
		name = ft_substr(arg, 0, equal_pos - arg);
		value = ft_strdup(equal_pos + 1);
	}
	else
	{
		name = ft_strdup(arg);
		value = NULL;
	}
	
	if (!is_valid_identifier(name))
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		free(name);
		free(value);
		return (1);
	}
	
	existing = ft_find_env(*env, name);
	if (existing && value)
	{
		free(existing->value);
		existing->value = value;
		free(name);
	}
	else if (!existing)
	{
		new_env = ft_calloc(1, sizeof(t_env));
		new_env->name = name;
		new_env->value = value;
		ft_addback_env(env, new_env);
	}
	else
	{
		free(name);
		free(value);
	}
	
	return (0);
}

int do_export(t_token *token, t_env **env)
{
	int i;
	int exit_status;
	
	if (!token || !token->tokens || !env)
		return (1);
		
	if (!token->tokens[1])
	{
		print_export_env(*env);
		return (0);
	}
	
	exit_status = 0;
	i = 1;
	while (token->tokens[i])
	{
		if (export_variable(token->tokens[i], env) != 0)
			exit_status = 1;
		i++;
	}
	return (exit_status);
}
