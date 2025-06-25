// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   unset.c                                            :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/05/11 21:01:25 by mmendiol          #+#    #+#             */
// /*   Updated: 2025/04/22 11:12:59 by anadal-g         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "../../includes/minishell.h"

static void remove_env_node(t_env **env_list, t_env *node)
{
	if (!node)
		return;
		
	if (node->prev)
		node->prev->next = node->next;
	else
		*env_list = node->next;
		
	if (node->next)
		node->next->prev = node->prev;
		
	free(node->name);
	free(node->value);
	free(node);
}

int do_unset(t_token *token, t_env **env)
{
	int i;
	t_env *env_node;
	
	if (!token || !token->tokens || !env)
		return (1);
		
	i = 1;
	while (token->tokens[i])
	{
		env_node = ft_find_env(*env, token->tokens[i]);
		if (env_node)
			remove_env_node(env, env_node);
		i++;
	}
	
	return (0);
}
