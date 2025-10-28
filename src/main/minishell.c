/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:15:04 by anadal-g          #+#    #+#             */
/*   Updated: 2025/10/28 20:28:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	g_signal_received = 0;

static void	init_shell(t_env **env_list, char **env)
{
	if (!env_list)
		return ;
	ft_init_env(env_list, env);
	if (*env_list)
		(*env_list)->last_out = 0;
	signal_input();
}

static int	process_input(char *input, t_token **tokens, t_env **env_list)
{
	char	*trimmed;

	if (!input || !tokens || !env_list)
		return (0);
	trimmed = ft_strtrim(input, " \t\n");
	if (!trimmed || !*trimmed)
	{
		free(trimmed);
		return (1);
	}
	free(trimmed);
	if (!validate_pipe_syntax(input))
	{
		if (*env_list)
			(*env_list)->last_out = 2;
		return (1);
	}
	add_history(input);
	free_tokens(tokens);
	create_tokens(input, tokens);
	if (!*tokens || !quotes_handler(tokens, input))
		return (1);
	lexerize(tokens, *env_list);
	executor(*tokens, env_list);
	return (1);
}

void	minishell_loop(t_token **tokens, t_env **env_list)
{
	char	*input;

	while (1)
	{
		g_signal_received = 0;
		input = readline("minishell$ ");
		if (!input)
			break ;
		if (g_signal_received == SIGINT && *env_list)
			(*env_list)->last_out = 130;
		if (!process_input(input, tokens, env_list))
			break ;
		free(input);
	}
	printf("exit\n");
}

int	main(int ac, char **av, char **env)
{
	t_token	**tokens;
	t_env	**env_list;

	(void)ac;
	(void)av;
	tokens = ft_calloc(1, sizeof(t_token *));
	env_list = ft_calloc(1, sizeof(t_env *));
	if (!tokens || !env_list)
		return (1);
	init_shell(env_list, env);
	minishell_loop(tokens, env_list);
	free_tokens(tokens);
	free_env(env_list);
	free(tokens);
	free(env_list);
	return (0);
}
