/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:07:53 by anadal-g          #+#    #+#             */
/*   Updated: 2025/10/28 21:34:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*ft_create_env_node(char *env_var)
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

t_env	*ft_new_env(char *name, char *value)
{
	t_env	*new_env;

	new_env = ft_calloc(1, sizeof(t_env));
	if (!new_env)
		return (NULL);
	new_env->name = ft_strdup(name);
	if (!new_env->name)
		return (free(new_env), NULL);
	if (value)
	{
		new_env->value = ft_strdup(value);
		if (!new_env->value)
		{
			free(new_env->name);
			return (free(new_env), NULL);
		}
	}
	else
		new_env->value = NULL;
	new_env->prev = NULL;
	new_env->next = NULL;
	new_env->last_out = 0;
	return (new_env);
}

void	ft_addback_env(t_env **lst, t_env *new)
{
	t_env	*mover;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	mover = *lst;
	while (mover->next != NULL)
		mover = mover->next;
	new->prev = mover;
	mover->next = new;
}

t_env	*ft_find_env(t_env *env_list, char *name)
{
	t_env	*token;

	token = env_list;
	while (token != NULL && name != NULL)
	{
		if (ft_strcmp(token->name, name) == 0)
			return (token);
		token = token->next;
	}
	return (NULL);
}

void	ft_del_env(t_env *env_node)
{
	if (!env_node)
	{
		printf("Error: Variable de entorno no inicializada\n");
		return ;
	}
	if (env_node->name != NULL)
		free(env_node->name);
	if (env_node->value != NULL)
		free(env_node->value);
	if (env_node->next != NULL)
		env_node->next->prev = env_node->prev;
	if (env_node->prev != NULL)
		env_node->prev->next = env_node->next;
	free(env_node);
}