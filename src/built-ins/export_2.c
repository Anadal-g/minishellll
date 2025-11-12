/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 10:54:37 by anadal-g          #+#    #+#             */
/*   Updated: 2025/11/12 11:41:56 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_env_vars(t_env *env)
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

t_env	**create_env_array(t_env *env, int count)
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

int	compare_env_names(const void *a, const void *b)
{
	t_env	*env_a;
	t_env	*env_b;

	env_a = *(t_env **)a;
	env_b = *(t_env **)b;
	return (ft_strcmp(env_a->name, env_b->name));
}

void	print_env_line(t_env *env)
{
	printf("declare -x %s", env->name);
	if (env->value)
		printf("=\"%s\"", env->value);
	printf("\n");
}

void	print_export_env(t_env *env)
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
