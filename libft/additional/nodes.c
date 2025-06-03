/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:04:16 by mmendiol          #+#    #+#             */
/*   Updated: 2024/10/16 18:20:06 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// typedef struct s_random_name	t_random_name;

// struct							s_random_name
// {
// 	int							id;
// 	char						*str;
// 	t_random_name				*prev;
// 	t_random_name				*next;
// };

// void	free_list(t_random_name **stack)
// {
// 	t_random_name	*aux;

// 	while (*stack)
// 	{
// 		aux = (*stack)->next;
// 		free(*stack);
// 		*stack = aux;
// 	}
// 	free(stack);
// }

// t_random_name	*create_node(int id, char *str)
// {
// 	t_random_name	*stack;

// 	stack = ft_calloc(1, sizeof(t_random_name));
// 	if (!stack)
// 		return (NULL);
// 	stack->id = id;
// 	stack->str = str;
// 	stack->prev = NULL;
// 	stack->next = NULL;
// 	return (stack);
// }

// t_random_name	*last_node(t_random_name *lst)
// {
// 	while (lst && lst->next != NULL)
// 		lst = lst->next;
// 	return (lst);
// }

// void	add_node_back(t_random_name **stack, t_random_name *new)
// {
// 	t_random_name	*aux;

// 	aux = last_node(*stack);
// 	if (*stack != NULL)
// 	{
// 		new->prev = aux;
// 		new->next = NULL;
// 		aux->next = new;
// 	}
// 	else
// 		*stack = new;
// }
