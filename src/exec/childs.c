/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:13:47 by anadal-g          #+#    #+#             */
/*   Updated: 2025/06/03 12:42:05 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void child_aux(t_token *token, t_env *env, int fd_in, int fd_out, int is_piped)
{
    char *path;
    char **env_array;

    if (!token || !token->tokens || !token->tokens[0])
    {
        ft_putstr_fd("minishell: invalid token\n", STDERR_FILENO);
        exit(1);
    }
    setup_child_io(fd_in, fd_out);
    if (is_builtin(token->command))
    {
        t_token *tmp = token;
        t_env *tmp_env = env;
        select_builtin(&tmp, &tmp_env, token->command);
        if (is_piped)
            exit(tmp_env->last_out);
        return;
    }
    path = handle_command_path(token, env, &env_array);
    if (!path)
    {
        ft_putstr_fd("minishell: ", STDERR_FILENO);
        ft_putstr_fd(token->tokens[0], STDERR_FILENO);
        ft_putstr_fd(": command not found\n", STDERR_FILENO);
        if (env_array)
            free_matrix(env_array);
        exit(127);  // Código estándar para "command not found"
    }
    execve(path, token->tokens, env_array);
    perror("execve");
    free(path);
    if (env_array)
        free_matrix(env_array);
    exit(126);  // Código estándar para error de execve
}


void first_child(t_token *token, t_env **env, int *fd)
{
    pid_t pid;
    int fd_in;
    int fd_out;

    pid = fork();
    if (pid == 0)
    {
        close(fd[0]); // Cerrar lectura del pipe
        fd_in = open_infile(token->infile);
        if (fd_in < 0 && token->infile) // Error solo si había redirección
            exit(1);
        if (fd_in < 0)
            fd_in = STDIN_FILENO;
        fd_out = open_outfile(token->outfile);
        if (fd_out < 0 && token->outfile) // Error solo si había redirección
        {
            if (fd_in != STDIN_FILENO)
                close(fd_in);
            exit(1);
        }
        if (fd_out < 0)
            fd_out = fd[1]; // Usar pipe si no hay redirección
        child_aux(token, *env, fd_in, fd_out, 1);
    }
    else if (pid < 0)
        exit_fork_pipe(FORK);
    close(fd[1]); // Padre cierra escritura del pipe
}


void mid_child(t_token *token, t_env **env, int *fd, int *new)
{
    pid_t pid;
    int fd_in;
    int fd_out;

    pid = fork();
    if (pid == 0)
    {
        close(new[0]); // Cerrar lectura del nuevo pipe
        fd_in = open_infile(token->infile);
        if (fd_in < 0 && token->infile) // Error solo si había redirección
            exit(1);
        if (fd_in < 0)
            fd_in = fd[0]; // Usar pipe anterior
        else
            close(fd[0]); // Cerrar pipe anterior si hay redirección
        fd_out = open_outfile(token->outfile);
        if (fd_out < 0 && token->outfile) // Error solo si había redirección
        {
            if (fd_in != STDIN_FILENO)
                close(fd_in);
            exit(1);
        }
        if (fd_out < 0)
            fd_out = new[1]; // Usar nuevo pipe
        else
            close(new[1]); // Cerrar nuevo pipe si hay redirección
        child_aux(token, *env, fd_in, fd_out, 1);
    }
    else if (pid < 0)
        exit_fork_pipe(FORK);
    close(fd[0]);
    close(fd[1]);
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
