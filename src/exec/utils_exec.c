/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:14:11 by anadal-g          #+#    #+#             */
/*   Updated: 2025/06/02 12:55:07 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// char *handle_command_path(t_token *token, t_env *env, char ***env_array)
// {
//     char *path;

//     if (!token || !token->tokens || !token->tokens[0])
//         return (NULL);
//     *env_array = env_to_array(env);
//     if (!*env_array)
//         return (NULL);
//     path = get_path(token->tokens[0], &env);
//     if (!path)
//     {
//         free_matrix(*env_array);
//         *env_array = NULL;
//     }
//     return (path);
// }

// void	setup_child_io(int fd_in, int fd_out)
// {
// 	dup2(fd_in, STDIN_FILENO);
// 	dup2(fd_out, STDOUT_FILENO);
// 	if (fd_in != STDIN_FILENO)
// 		close(fd_in);
// 	if (fd_out != STDOUT_FILENO && fd_out != STDERR_FILENO)
// 		close(fd_out);
// }

int validate_token(t_token *token)
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

int	is_full_path(char *cmd)
{
	while (*cmd)
	{
		if (*cmd == '/')
			return (1);
		cmd++;
	}
	return (0);
}

char	*search_in_path(char *cmd, char **path_list)
{
	char	*path;
	char	*tmp;
	int		i;

	i = 0;
	while (path_list && path_list[i])
	{
		tmp = ft_strjoin(path_list[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

void	perror_error(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}
