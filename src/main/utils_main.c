/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinamc <carolinamc@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:15:04 by anadal-g          #+#    #+#             */
/*   Updated: 2025/07/16 13:36:40 by carolinamc       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_io_files(t_token *aux)
{
	t_iofile	*io_aux;

	if (aux->infile)
	{
		io_aux = aux->infile;
		while (io_aux)
		{
			printf("INFILE\t\t->\t[%s] (TYPE: %d)\n",
				io_aux->name, io_aux->type);
			io_aux = io_aux->next;
		}
	}
	if (aux->outfile)
	{
		io_aux = aux->outfile;
		while (io_aux)
		{
			printf("OUTFILE\t\t->\t[%s] (TYPE: %d)\n",
				io_aux->name, io_aux->type);
			io_aux = io_aux->next;
		}
	}
	printf("PREV NODE\t->\t%p\n", aux->prev);
	printf("NEXT NODE\t->\t%p\n\n\n", aux->next);
}

void	show_lst(t_token **stack)
{
	t_token	*aux;
	int		i;

	if (!stack || !*stack)
		return ;
	aux = *stack;
	while (aux != NULL)
	{
		printf("STACK NODE\t->\t%p\n", *stack);
		printf("NODE\t\t->\t%p\n", aux);
		if (aux->prev)
			printf("PREV COMMAND[%d]\t->\t%s\n", aux->prev->id,
				aux->prev->command);
		printf("NODE COMMAND[%d]\t->\t%s\n", aux->id, aux->command);
		if (aux->tokens)
		{
			i = -1;
			while (aux->tokens[++i])
				printf("TOKEN[%d]\t->\t[%s]\n", i, aux->tokens[i]);
		}
		print_io_files(aux);
		aux = aux->next;
	}
}
