/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinamc <carolinamc@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:14:11 by anadal-g          #+#    #+#             */
/*   Updated: 2025/07/23 12:58:26 by carolinamc       ###   ########.fr       */
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

void	read_till_character_redir(char *input, int *start, int *counter)
{
	if (!input || !start || !counter)
		return ;
	*counter = *start;
	while (input[*counter])
	{
		if (input[*counter] == '<' || input[*counter] == '>')
			break ;
		(*counter)++;
	}
}

int	handle_trim_and_store(char *substr, char **dest)
{
	char	*trimmed;

	trimmed = ft_strtrim(substr, " ");
	free(substr);
	if (!trimmed)
		return (0);
	*dest = trimmed;
	return (1);
}

void	setup_child_io(int fd_in, int fd_out)
{
	if (fd_in != STDIN_FILENO)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (fd_out != STDOUT_FILENO)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
}

char	*handle_command_path(t_token *token, t_env *env, char ***env_array)
{
	char	*path;

	if (!token || !token->tokens || !token->tokens[0] || !env)
		return (NULL);
	*env_array = env_to_array(env);
	if (!*env_array)
		return (NULL);
	path = get_path(token->tokens[0], &env);
	if (!path)
	{
		free_matrix(*env_array);
		*env_array = NULL;
		return (NULL);
	}
	return (path);
}
