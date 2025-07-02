/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:13:21 by anadal-g          #+#    #+#             */
/*   Updated: 2025/06/30 13:14:53 by anadal-g         ###   ########.fr       */
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

static void child_process(t_token *token, t_env **env)
{
	int fd_in;
	int fd_out;
	char *path;
	char **env_array;

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

	if (is_builtin(token->tokens[0]))
	{
		select_builtin(&token, env, token->command);
		exit((*env)->last_out);
	}

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

	// Parent process waits for child
	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid");
		if (*env)
			(*env)->last_out = 1;
		return;
	}

	if (WIFEXITED(status))
		(*env)->last_out = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		(*env)->last_out = 128 + WTERMSIG(status);
}

void exe_built_ins(t_token *token, t_env **env)
{
	int fd_in = -1;
	int fd_out = -1;
	int saved_stdin = -1;
	int saved_stdout = -1;

	if (!token || !token->command || !env || !*env)
	{
		if (env && *env)
			(*env)->last_out = 1;
		return;
	}

	fd_in = open_infile(token->infile);
	if (fd_in < 0 && token->infile)
	{
		(*env)->last_out = 1;
		return;
	}

	fd_out = open_outfile(token->outfile);
	if (fd_out < 0 && token->outfile)
	{
		if (fd_in >= 0 && fd_in != STDIN_FILENO)
			close(fd_in);
		(*env)->last_out = 1;
		return;
	}

	if (fd_in != STDIN_FILENO && fd_in >= 0)
		saved_stdin = dup(STDIN_FILENO);
	if (fd_out != STDOUT_FILENO && fd_out >= 0)
		saved_stdout = dup(STDOUT_FILENO);
		
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

	select_builtin(&token, env, token->command);

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
