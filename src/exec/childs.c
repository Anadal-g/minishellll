/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinamc <carolinamc@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:13:47 by anadal-g          #+#    #+#             */
/*   Updated: 2025/07/22 13:08:17 by carolinamc       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_builtin(t_token *token, t_env *env, int is_piped)
{
	t_token	*tmp;
	t_env	*tmp_env;

	tmp = token;
	tmp_env = env;
	select_builtin(&tmp, &tmp_env, token->command);
	if (is_piped)
		exit(tmp_env->last_out);
}

void	exec_command(char *path, t_token *token, char **env_array)
{
	if (!path)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(token->tokens[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		if (env_array)
			free_matrix(env_array);
		exit(127);
	}
	execve(path, token->tokens, env_array);
	perror("execve");
	free(path);
	if (env_array)
		free_matrix(env_array);
	exit(126);
}

void	child_aux(t_token *token, t_env *env, int fds[2], int is_piped)
{
	char	*path;
	char	**env_array;

	if (!token || !token->tokens || !token->tokens[0])
	{
		ft_putstr_fd("minishell: invalid token\n", STDERR_FILENO);
		exit(1);
	}
	setup_child_io(fds[0], fds[1]);
	if (is_builtin(token->tokens[0]))
	{
		handle_builtin(token, env, is_piped);
		return ;
	}
	path = handle_command_path(token, env, &env_array);
	exec_command(path, token, env_array);
}

void	wait_childs(pid_t final_pid, int *last_out)
{
	pid_t	current_pid;
	int		status;

	while (1)
	{
		current_pid = waitpid(-1, &status, 0);
		if (current_pid <= 0)
			break ;
		if (current_pid == final_pid)
		{
			if (WIFEXITED(status))
				*last_out = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				*last_out = 128 + WTERMSIG(status);
		}
	}
}
