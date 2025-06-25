/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:24:16 by anadal-g          #+#    #+#             */
/*   Updated: 2025/06/25 13:34:07 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int count_tokens(t_token *tokens)
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

static void one_command(t_token *token, t_env **env)
{
	if (!token || !token->tokens || !token->tokens[0])
		return;
		
	if (is_builtin(token->tokens[0]))
		exe_built_ins(token, env);
	else
		exe_one_cmd(token, env);
}

static void execute_pipeline_child(t_token *current, t_env **env, int *prev_fd, int *curr_fd, int is_last)
{
	int fd_in = STDIN_FILENO;
	int fd_out = STDOUT_FILENO;
	
	// Setup input
	if (current->infile)
	{
		fd_in = open_infile(current->infile);
		if (fd_in < 0)
			exit(1);
	}
	else if (prev_fd[0] != -1)
	{
		fd_in = prev_fd[0];
	}
	
	// Setup output
	if (current->outfile)
	{
		fd_out = open_outfile(current->outfile);
		if (fd_out < 0)
		{
			if (fd_in != STDIN_FILENO)
				close(fd_in);
			exit(1);
		}
	}
	else if (!is_last)
	{
		fd_out = curr_fd[1];
	}
	
	// Close unused pipe ends
	if (prev_fd[0] != -1 && fd_in != prev_fd[0])
		close(prev_fd[0]);
	if (prev_fd[1] != -1)
		close(prev_fd[1]);
	if (!is_last)
	{
		if (fd_out != curr_fd[1])
			close(curr_fd[1]);
		close(curr_fd[0]);
	}
	
	// Setup file descriptors
	setup_child_io(fd_in, fd_out);
	
	// Execute command
	if (is_builtin(current->tokens[0]))
	{
		select_builtin(&current, env, current->command);
		exit((*env)->last_out);
	}
	else
	{
		char *path;
		char **env_array;
		
		path = handle_command_path(current, *env, &env_array);
		if (!path)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(current->tokens[0], STDERR_FILENO);
			ft_putstr_fd(": command not found\n", STDERR_FILENO);
			if (env_array)
				free_matrix(env_array);
			exit(127);
		}
		execve(path, current->tokens, env_array);
		perror("execve");
		free(path);
		if (env_array)
			free_matrix(env_array);
		exit(126);
	}
}

static void two_or_more_cmds(t_token *tokens, t_env **env)
{
	t_token *current;
	int prev_fd[2] = {-1, -1};
	int curr_fd[2];
	pid_t pid;
	pid_t last_pid = -1;

	current = tokens;
	while (current)
	{
		// Create pipe if not last command
		if (current->next)
		{
			if (pipe(curr_fd) < 0)
				exit_fork_pipe(PIPE);
		}
		
		pid = fork();
		if (pid < 0)
			exit_fork_pipe(FORK);
		
		if (pid == 0) // Child process
		{
			execute_pipeline_child(current, env, prev_fd, curr_fd, !current->next);
		}
		
		// Parent process: close previous pipe and update for next iteration
		if (prev_fd[0] != -1)
		{
			close(prev_fd[0]);
			close(prev_fd[1]);
		}
		
		if (current->next)
		{
			prev_fd[0] = curr_fd[0];
			prev_fd[1] = curr_fd[1];
		}
		else
		{
			last_pid = pid;
		}
		
		current = current->next;
	}
	
	// Close final pipe in parent
	if (prev_fd[0] != -1)
	{
		close(prev_fd[0]);
		close(prev_fd[1]);
	}
	
	wait_childs(last_pid, &(*env)->last_out);
}

void executor(t_token *tokens, t_env **env)
{
	int cmd_count;
	
	if (!tokens)
		return;
		
	cmd_count = count_tokens(tokens);
	
	if (cmd_count == 1)
		one_command(tokens, env);
	else
		two_or_more_cmds(tokens, env);
}