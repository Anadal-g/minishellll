/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:24:16 by anadal-g          #+#    #+#             */
/*   Updated: 2025/06/03 12:44:36 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void close_unused_fds(int *prev_fd, int *current_fd, int is_first, int is_last)
{
    if (!is_first && prev_fd[0] != -1)
    {
        close(prev_fd[0]);
        close(prev_fd[1]);
    }
    
    if (!is_last && current_fd[0] != -1)
    {
        close(current_fd[0]);  // Cerrar lectura en el hijo
    }
}

static int	count_tokens(t_token *tokens)
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

int handle_echo_input_redirection(t_token *token)
{
    // echo normalmente no lee de stdin, pero si hay redirección <
    // simplemente la ignoramos (comportamiento de bash)
    if (ft_strcmp(token->command, "echo") == 0 && token->infile)
    {
        // Ejecutar echo normalmente, ignorando la redirección de entrada
        return (do_echo(token));
    }
    return (-1); // No es echo o no hay redirección, manejar normalmente
}

static void	one_command(t_token *token, t_env **env)
{
    int special_result;
    
    special_result = handle_echo_input_redirection(token);
    if (special_result != -1)
    {
        if (*env)
            (*env)->last_out = special_result;
        return;
    }
	if (is_builtin(token->command))
		exe_built_ins(token, env);
	else
		exe_one_cmd(token, env);
}
static void two_or_more_cmds(t_token *tokens, t_env **env)
{
    t_token *current;
    int fd[2];
    int prev_fd[2];
    pid_t pid;
    int is_first;
    pid_t last_pid;

    current = tokens;
    is_first = 1;
    prev_fd[0] = -1;
    prev_fd[1] = -1;

    while (current)
    {
        if (current->next)
        {
            if (pipe(fd) < 0)
                exit_fork_pipe(PIPE);
        }
        pid = fork();
        if (pid < 0)
            exit_fork_pipe(FORK);

        if (pid == 0) // Proceso hijo
        {
            if (!is_first)
            {
                dup2(prev_fd[0], STDIN_FILENO);
                close(prev_fd[0]);
                close(prev_fd[1]);
            }
            if (current->next)
            {
                close(fd[0]);
                dup2(fd[1], STDOUT_FILENO);
                close(fd[1]);
            }
            int fd_in = open_infile(current->infile);
            if (fd_in >= 0 && fd_in != STDIN_FILENO)
            {
                dup2(fd_in, STDIN_FILENO);
                close(fd_in);
            }
            else if (fd_in < 0 && current->infile)
                exit(1); // Error en redirección
            int fd_out = open_outfile(current->outfile);
            if (fd_out >= 0 && fd_out != STDOUT_FILENO)
            {
                dup2(fd_out, STDOUT_FILENO);
                close(fd_out);
            }
            else if (fd_out < 0 && current->outfile)
                exit(1); // Error en redirección
            if (is_builtin(current->command))
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
        if (!is_first)
        {
            close(prev_fd[0]);
            close(prev_fd[1]);
        }
        if (current->next)
        {
            prev_fd[0] = fd[0];
            prev_fd[1] = fd[1];
        }
        else
            last_pid = pid;
        is_first = 0;
        current = current->next;
    }
    if (prev_fd[0] != -1)
    {
        close(prev_fd[0]);
        close(prev_fd[1]);
    }

    wait_childs(last_pid, &(*env)->last_out);
}

void	executor(t_token *tokens, t_env **env)
{
	int cmd_count = count_tokens(tokens);

	if (cmd_count == 1)
		one_command(tokens, env);
	else
		two_or_more_cmds(tokens, env);
}
