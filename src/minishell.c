/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:11:15 by anadal-g          #+#    #+#             */
/*   Updated: 2025/06/25 13:17:43 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int g_signal_received = 0;

void show_lst(t_token **stack)
{
	t_token		*aux;
	int			i;
	t_iofile	*io_aux;

	aux = *stack;
	while (aux != NULL)
	{
		printf("STACK NODE	->	%p\n", *stack);
		printf("NODE		->	%p\n", aux);
		if (aux->prev)
			printf("PREV COMMAND[%d]	->	%s\n", aux->prev->id,
				aux->prev->command);
		printf("NODE COMMAND[%d]	->	%s\n", aux->id, aux->command);
		if (aux->tokens)
		{
			i = -1;
			while (aux->tokens[++i])
				printf("TOKEN[%d]	->	[%s]\n", i, aux->tokens[i]);
		}
		if (aux->infile)
		{
			io_aux = aux->infile;
			while (io_aux)
			{
				printf("INFILE		->	[%s] (TYPE: %d)\n", io_aux->name,
					io_aux->type);
				io_aux = io_aux->next;
			}
		}
		if (aux->outfile)
		{
			io_aux = aux->outfile;
			while (io_aux)
			{
				printf("OUTFILE		->	[%s] (TYPE: %d)\n", io_aux->name,
					io_aux->type);
				io_aux = io_aux->next;
			}
		}
		printf("PREV NODE	->	%p\n", aux->prev);
		printf("NEXT NODE	->	%p\n\n\n", aux->next);
		aux = aux->next;
	}
}

static void init_shell(t_env **env_list, char **env)
{
	ft_init_env(env_list, env);
	if (*env_list)
		(*env_list)->last_out = 0;
	signal_input();
}

static int process_input(char *input, t_token **tokens, t_env **env_list)
{
	if (!input)
		return (0);
	
	if (!validate_pipe_syntax(input))
	{
		if (*env_list)
			(*env_list)->last_out = 2;
		return (1);
	}
	
	add_history(input);
	free_tokens(tokens);
	create_tokens(input, tokens);
	
	if (!*tokens)
		return (1);
		
	if (!quotes_handler(tokens, input))
		return (1);
		
	lexerize(tokens, *env_list);
	executor(*tokens, env_list);
	return (1);
}

int main(int ac, char **av, char **env)
{
	t_token		**tokens;
	t_env		**env_list;
	char		*input;

	(void)ac;
	(void)av;
	
	tokens = ft_calloc(1, sizeof(t_token *));
	env_list = ft_calloc(1, sizeof(t_env *));
	
	if (!tokens || !env_list)
		return (1);
		
	init_shell(env_list, env);
	
	while (1)
	{
		input = readline("minishell$ ");
		
		if (!input)
		{
			printf("exit\n");
			break;
		}
		
		if (!process_input(input, tokens, env_list))
			break;
			
		free(input);
	}
	
	free_tokens(tokens);
	free_env(env_list);
	free(tokens);
	free(env_list);
	return (0);
}
