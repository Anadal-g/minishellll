/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 16:59:23 by anadal-g          #+#    #+#             */
/*   Updated: 2025/11/12 10:38:56 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_env_vars(t_env *env)
{
	int		count;
	t_env	*current;

	count = 0;
	current = env;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

static t_env	**create_env_array(t_env *env, int count)
{
	t_env	**array;
	t_env	*cur;
	int		i;

	array = malloc(sizeof(t_env *) * count);
	if (!array)
		return (NULL);
	cur = env;
	i = 0;
	while (cur && i < count)
	{
		array[i] = cur;
		cur = cur->next;
		i++;
	}
	return (array);
}

static int	compare_env_names(const void *a, const void *b)
{
	t_env	*env_a;
	t_env	*env_b;

	env_a = *(t_env **)a;
	env_b = *(t_env **)b;
	return (ft_strcmp(env_a->name, env_b->name));
}

static void	print_env_line(t_env *env)
{
	printf("declare -x %s", env->name);
	if (env->value)
		printf("=\"%s\"", env->value);
	printf("\n");
}

static void	print_export_env(t_env *env)
{
	t_env	**array;
	int		count;
	int		i;

	if (!env)
		return ;
	count = count_env_vars(env);
	if (count == 0)
		return ;
	array = create_env_array(env, count);
	if (!array)
		return ;
	qsort(array, count, sizeof(t_env *), compare_env_names);
	i = 0;
	while (i < count)
		print_env_line(array[i++]);
	free(array);
}

static int	is_valid_identifier(char *str)
{
	int	i;

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

static int	handle_existing_env(t_env *existing, char *value, char *name)
{
	if (existing && value)
	{
		free(existing->value);
		existing->value = value;
		free(name);
		return (1);
	}
	return (0);
}

static int	create_new_env(char *name, char *value, t_env **env)
{
	t_env	*new_env;

	new_env = ft_calloc(1, sizeof(t_env));
	if (!new_env)
	{
		free(name);
		free(value);
		return (1);
	}
	new_env->name = name;
	new_env->value = value;
	new_env->next = NULL;
	new_env->prev = NULL;
	new_env->last_out = 0;
	ft_addback_env(env, new_env);
	return (0);
}

static int	parse_export_arg(char *arg, t_pair *pair)
{
	char	*eq;

	eq = ft_strchr(arg, '=');
	if (eq)
	{
		pair->name = ft_substr(arg, 0, eq - arg);
		pair->value = ft_strdup(eq + 1);
	}
	else
	{
		pair->name = ft_strdup(arg);
		pair->value = NULL;
	}
	if (!pair->name)
		return (1);
	return (0);
}

static int	handle_invalid_id(char *arg, t_pair *pair)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	free(pair->name);
	free(pair->value);
	return (1);
}

static int	export_variable(char *arg, t_env **env)
{
	t_pair	pair;
	t_env	*existing;

	if (parse_export_arg(arg, &pair))
		return (1);
	if (!is_valid_identifier(pair.name))
		return (handle_invalid_id(arg, &pair));
	existing = ft_find_env(*env, pair.name);
	if (handle_existing_env(existing, pair.value, pair.name))
		return (0);
	return (create_new_env(pair.name, pair.value, env));
}

int	do_export(t_token *token, t_env **env)
{
	int	i;
	int	status;

	if (!token || !token->tokens || !env)
		return (1);
	if (!token->tokens[1])
		return (print_export_env(*env), 0);
	status = 0;
	i = 1;
	while (token->tokens[i])
	{
		if (export_variable(token->tokens[i], env) != 0)
			status = 1;
		i++;
	}
	return (status);
}
