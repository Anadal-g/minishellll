/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:07:53 by anadal-g          #+#    #+#             */
/*   Updated: 2025/03/27 11:49:48 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#include "../../includes/minishell.h"

char **env_to_array(t_env *env)
{
    int     count = 0;
    t_env   *tmp = env;
    char    **env_array;
    char    *var;
    
    while (tmp)
    {
        count++;
        tmp = tmp->next;
    }
    env_array = malloc(sizeof(char *) * (count + 1));
    if (!env_array)
        return (NULL);
    tmp = env;
    count = 0;
    while (tmp)
    {
        var = ft_strjoin(tmp->name, "=");
        env_array[count] = ft_strjoin(var, tmp->value);
        free(var);
        if (!env_array[count])
        {
            free_matrix(env_array);
            return (NULL);
        }
        count++;
        tmp = tmp->next;
    }
    env_array[count] = NULL;
    return (env_array);
}

t_env	*ft_new_env(char *name, char *value)
{
	t_env	*new_env;

	new_env = ft_calloc(1, sizeof(t_env));
	if (new_env == 0)
		return (NULL);
	new_env->name = ft_strdup(name);
	if (new_env->name == NULL)
	{
		free(new_env);
		return (NULL);
	}
	if (value != NULL)
	{
		free(new_env->name);
		free(new_env);
		return (NULL);
	}
	new_env->prev = NULL;
	new_env->next = NULL;
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
		if (ft_strncmp(token->name, name, ft_strlen(name)) == 0)
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
