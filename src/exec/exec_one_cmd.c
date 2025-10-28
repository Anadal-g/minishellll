/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:13:21 by anadal-g          #+#    #+#             */
/*   Updated: 2025/10/28 19:53:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void setup_child_io(int fd_in, int fd_out)
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

char *handle_command_path(t_token *token, t_env *env, char ***env_array)
{
	char *path;

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

static int setup_child_fds(t_token *token, int *fd_in, int *fd_out)
{
	*fd_in = open_infile(token->infile);
	if (*fd_in < 0 && token->infile)
		return (0);
	if (*fd_in < 0)
		*fd_in = STDIN_FILENO;
	*fd_out = open_outfile(token->outfile);
	if (*fd_out < 0 && token->outfile)
	{
		if (*fd_in != STDIN_FILENO)
			close(*fd_in);
		return (0);
	}
	if (*fd_out < 0)
		*fd_out = STDOUT_FILENO;
	return (1);
}

static void execute_child_builtin(t_token *token, t_env **env)
{
	select_builtin(&token, env, token->command);
	exit((*env)->last_out);
}

static void execute_child_command(t_token *token, t_env **env)
{
	char *path;
	char **env_array;

	path = handle_command_path(token, *env, &env_array);
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

static void child_process(t_token *token, t_env **env)
{
	int fd_in;
	int fd_out;

	if (!token || !token->tokens || !token->tokens[0] || !env || !*env)
		exit(1);
	if (!setup_child_fds(token, &fd_in, &fd_out))
		exit(1);
	setup_child_io(fd_in, fd_out);
	if (is_builtin(token->tokens[0]))
		execute_child_builtin(token, env);
	execute_child_command(token, env);
}

static void handle_wait_status(int status, t_env **env)
{
	if (WIFEXITED(status))
		(*env)->last_out = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		(*env)->last_out = 128 + WTERMSIG(status);
}

void exe_one_cmd(t_token *token, t_env **env)
{
	pid_t pid;
	int status;

	if (!token || !env || !*env)
		return;
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		if (*env)
			(*env)->last_out = 1;
		return;
	}
	if (pid == 0)
		child_process(token, env);
	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid");
		if (*env)
			(*env)->last_out = 1;
		return;
	}
	handle_wait_status(status, env);
}

static int open_builtin_fds(t_token *token, int *fd_in, int *fd_out)
{
	*fd_in = open_infile(token->infile);
	if (*fd_in < 0 && token->infile)
		return (0);
	*fd_out = open_outfile(token->outfile);
	if (*fd_out < 0 && token->outfile)
	{
		if (*fd_in >= 0 && *fd_in != STDIN_FILENO)
			close(*fd_in);
		return (0);
	}
	return (1);
}

static void save_std_fds(int fd_in, int fd_out, int *saved_in, int *saved_out)
{
	if (fd_in != STDIN_FILENO && fd_in >= 0)
		*saved_in = dup(STDIN_FILENO);
	if (fd_out != STDOUT_FILENO && fd_out >= 0)
		*saved_out = dup(STDOUT_FILENO);
}

static void redirect_builtin_fds(int fd_in, int fd_out)
{
	if (fd_in != STDIN_FILENO && fd_in >= 0)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (fd_out != STDOUT_FILENO && fd_out >= 0)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
}

static void restore_std_fds(int saved_stdin, int saved_stdout)
{
	if (saved_stdin >= 0)
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
	if (saved_stdout >= 0)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
}

void exe_built_ins(t_token *token, t_env **env)
{
	int fd_in;
	int fd_out;
	int saved_stdin;
	int saved_stdout;

	saved_stdin = -1;
	saved_stdout = -1;
	if (!token || !token->command || !env || !*env)
	{
		if (env && *env)
			(*env)->last_out = 1;
		return;
	}
	if (!open_builtin_fds(token, &fd_in, &fd_out))
	{
		(*env)->last_out = 1;
		return;
	}
	save_std_fds(fd_in, fd_out, &saved_stdin, &saved_stdout);
	redirect_builtin_fds(fd_in, fd_out);
	select_builtin(&token, env, token->command);
	restore_std_fds(saved_stdin, saved_stdout);
}
