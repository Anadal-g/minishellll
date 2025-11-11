/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:14:11 by anadal-g          #+#    #+#             */
/*   Updated: 2025/11/11 12:59:37 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	validate_token(t_token *token)
{
	if (!token)
		return (0);
	if (!token->tokens)
		return (0);
	if (!token->tokens[0])
		return (0);
	if (!token->command)
		return (0);
	return (1);
}

int	count_tokens(t_token *tokens)
{
	int		count;
	t_token	*current;

	count = 0;
	current = tokens;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

void	one_command(t_token *token, t_env **env)
{
	if (!token || !token->tokens || !token->tokens[0])
		return ;
	if (is_builtin(token->tokens[0]))
		exe_built_ins(token, env);
	else
		exe_one_cmd(token, env);
}

int	setup_pipeline_input(t_token *current, int *prev_fd, int *fd_in)
{
	if (current->infile)
	{
		*fd_in = open_infile(current->infile);
		if (*fd_in < 0)
			return (0);
	}
	else if (prev_fd[0] != -1)
		*fd_in = prev_fd[0];
	return (1);
}

int	setup_pipeline_output(t_token *current, int *curr_fd, int *fd_out,
		int is_last)
{
	if (current->outfile)
	{
		*fd_out = open_outfile(current->outfile);
		if (*fd_out < 0)
			return (0);
	}
	else if (!is_last)
		*fd_out = curr_fd[1];
	return (1);
}
