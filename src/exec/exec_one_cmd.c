/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinamc <carolinamc@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:13:21 by anadal-g          #+#    #+#             */
/*   Updated: 2025/07/23 12:59:51 by carolinamc       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_exec(char *path, t_token *token, char **env_array)
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
	if (execve(path, token->tokens, env_array) == -1)
	{
		perror("execve");
		free(path);
		if (env_array)
			free_matrix(env_array);
		exit(126);
	}
}

static void	execute_child_command(t_token *token, t_env **env)
{
	char	*path;
	char	**env_array;

	if (is_builtin(token->tokens[0]))
	{
		select_builtin(&token, env, token->command);
		exit((*env)->last_out);
	}
	path = handle_command_path(token, *env, &env_array);
	handle_exec(path, token, env_array);
}

static void	child_process(t_token *token, t_env **env)
{
	int		fd_in;
	int		fd_out;

	if (!token || !token->tokens || !token->tokens[0] || !env || !*env)
		exit(1);
	fd_in = open_infile(token->infile);
	if (fd_in < 0 && token->infile)
		exit(1);
	if (fd_in < 0)
		fd_in = STDIN_FILENO;
	fd_out = open_outfile(token->outfile);
	if (fd_out < 0 && token->outfile)
	{
		if (fd_in != STDIN_FILENO)
			close(fd_in);
		exit(1);
	}
	if (fd_out < 0)
		fd_out = STDOUT_FILENO;
	setup_child_io(fd_in, fd_out);
	execute_child_command(token, env);
}

void	exe_one_cmd(t_token *token, t_env **env)
{
	pid_t	pid;
	int		status;

	if (!token || !env || !*env)
		return ;
	pid = fork();
	if (pid < 0)
		exit_fork_pipe(FORK);
	if (pid == 0)
		child_process(token, env);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		(*env)->last_out = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		(*env)->last_out = 128 + WTERMSIG(status);
}

void	exe_built_ins(t_token *token, t_env **env)
{
	int	fd_in;
	int	fd_out;
	int	saved_stdin;
	int	saved_stdout;

	fd_in = -1;
	fd_out = -1;
	saved_stdin = -1;
	saved_stdout = -1;
	if (!token || !token->command || !env || !*env)
	{
		if (env && *env)
			(*env)->last_out = 1;
		return ;
	}
	if (!open_builtin_fds(token, env, &fd_in, &fd_out))
		return ;
	dup_builtin_fds(fd_in, fd_out, &saved_stdin, &saved_stdout);
	select_builtin(&token, env, token->command);
	restore_builtin_fds(saved_stdin, saved_stdout);
}
