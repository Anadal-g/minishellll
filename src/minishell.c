/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:11:15 by anadal-g          #+#    #+#             */
/*   Updated: 2025/06/03 12:21:49 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int validate_pipe_syntax(char *input)
{
    int i = 0;
    int in_quotes = 0;
    char quote_char = 0;
    
    if (!input || !*input)
        return (1);
    while (input[i] && (input[i] == ' ' || input[i] == '\t'))
        i++;
    if (input[i] == '|')
    {
        ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", STDERR_FILENO);
        return (0);
    }
    while (input[i])
    {
        if ((input[i] == '"' || input[i] == '\'') && !in_quotes)
        {
            in_quotes = 1;
            quote_char = input[i];
        }
        else if (input[i] == quote_char && in_quotes)
        {
            in_quotes = 0;
            quote_char = 0;
        }
        else if (input[i] == '|' && !in_quotes)
        {
            int j = i + 1;
            while (input[j] && (input[j] == ' ' || input[j] == '\t'))
                j++;
            if (input[j] == '|')
            {
                ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", STDERR_FILENO);
                return (0);
            }
            if (!input[j])
            {
                ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", STDERR_FILENO);
                return (0);
            }
        }
        i++;
    }
    return (1);
}

int validate_input_syntax(char *input)
{
    int i = 0;
    int pipe_count = 0;
    int consecutive_pipes = 0;
    int has_content_before_pipe = 0;
    int has_content_after_pipe = 0;
    int in_quotes = 0;
    char quote_char = 0;
    
    if (!input || !*input)
        return (1);
    while (input[i] && (input[i] == ' ' || input[i] == '\t'))
        i++;
    if (input[i] == '|')
    {
        ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", STDERR_FILENO);
        return (0);
    }
    while (input[i])
    {
        if ((input[i] == '"' || input[i] == '\'') && !in_quotes)
        {
            in_quotes = 1;
            quote_char = input[i];
        }
        else if (input[i] == quote_char && in_quotes)
        {
            in_quotes = 0;
            quote_char = 0;
        }
        else if (input[i] == '|' && !in_quotes)
        {
            pipe_count++;
            consecutive_pipes++;
            if (consecutive_pipes > 1)
            {
                ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", STDERR_FILENO);
                return (0);
            }
            int j = i + 1;
            while (input[j] && (input[j] == ' ' || input[j] == '\t'))
                j++;
            
            if (!input[j] || input[j] == '|')
            {
                ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", STDERR_FILENO);
                return (0);
            }
            has_content_after_pipe = 1;
        }
        else if (input[i] != ' ' && input[i] != '\t')
        {
            consecutive_pipes = 0;
            if (pipe_count == 0)
                has_content_before_pipe = 1;
        }
        i++;
    }
    if (in_quotes)
    {
        ft_putstr_fd("minishell: syntax error: unclosed quotes\n", STDERR_FILENO);
        return (0);
    } 
    return (1);
}


void	show_lst(t_token **stack)
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

void	show_env_list(t_env **env_list)
{
	t_env	*current_node;

	current_node = *env_list;
	while (current_node != NULL)
	{
		printf("NODE ADDRESS  ->  %p\n", current_node);
		if (current_node->prev)
			printf("PREV NODE     ->  %p\n", current_node->prev);
		else
			printf("PREV NODE     ->  [None]\n");
		printf("ENV NAME      ->  %s\n", current_node->name);
		printf("ENV VALUE     ->  %s\n", current_node->value);
		if (current_node->next)
			printf("NEXT NODE     ->  %p\n\n", current_node->next);
		else
			printf("NEXT NODE     ->  [None]\n\n");
		current_node = current_node->next;
	}
}
int main(int ac, char **av, char **env)
{
    t_token **tokens;
    t_env **env_list;
    char *input;

    tokens = ft_calloc(1, sizeof(t_token *));
    env_list = ft_calloc(1, sizeof(t_env *));
    if (ac == 0 && av == NULL && env == NULL)
        printf("Hello");
    ft_init_env(env_list, env);
    
    while (1)
    {
        input = readline(" 💻 $ ");
        if (!input)
            break;
        
        // NUEVA VALIDACIÓN AQUÍ - ANTES DE PROCESAR
        if (!validate_pipe_syntax(input))
        {
            if (*env_list)
                (*env_list)->last_out = 2;
            free(input);
            continue;
        }
        
        free_tokens(tokens);
        create_tokens(input, tokens);
        if (!quotes_handler(tokens, input))
            continue;
        lexerize(tokens);
        executor(*tokens, env_list);
        free(input);
    }
    free(tokens);
    return (0);
}