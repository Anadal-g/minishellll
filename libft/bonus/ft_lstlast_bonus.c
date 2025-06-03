/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 19:26:11 by mmendiol          #+#    #+#             */
/*   Updated: 2024/03/12 17:33:57 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	while (lst && lst->next != NULL)
		lst = lst->next;
	return (lst);
}
/*
#include "ft_lstadd_back_bonus.c"
#include "ft_lstnew_bonus.c"
#include "ft_calloc.c"
#include "ft_bzero.c"
#include "ft_memset.c"
int main() {
    t_list *list;
	
	list = NULL;
    ft_lstadd_back(&list, ft_lstnew("Element 1"));
    ft_lstadd_back(&list, ft_lstnew("Element 2"));
    ft_lstadd_back(&list, ft_lstnew("Element 3"));

    t_list *lastElement = ft_lstlast(list);

    printf("Content: %s\n", (char *)(lastElement->content));

    return 0;
}*/