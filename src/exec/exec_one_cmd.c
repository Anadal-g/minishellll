/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:13:21 by anadal-g          #+#    #+#             */
/*   Updated: 2025/06/03 12:40:52 by anadal-g         ###   ########.fr       */
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
    
    *env_array = env_to_array(env);
    if (!*env_array)
        return (NULL);
    
    if (!token->tokens[0])
    {
        free_matrix(*env_array);
        *env_array = NULL;
        return (NULL);
    }
    
    path = get_path(token->tokens[0], &env);
    if (!path)
    {
        free_matrix(*env_array);
        *env_array = NULL;
        return (NULL);
    }
    
    return (path);
}

void child_process(t_token *token, t_env **env)
{
    int fd_in;
    int fd_out;

    if (!token || !token->tokens || !token->tokens[0])
    {
        ft_putstr_fd("minishell: invalid token\n", STDERR_FILENO);
        exit(1);
    }
    fd_in = open_infile(token->infile);
    if (fd_in < 0 && token->infile) // Solo error si había redirección
        exit(1);
    if (fd_in < 0)
        fd_in = STDIN_FILENO;
    fd_out = open_outfile(token->outfile);
    if (fd_out < 0 && token->outfile) // Solo error si había redirección
    {
        if (fd_in != STDIN_FILENO)
            close(fd_in);
        exit(1);
    }
    if (fd_out < 0)
        fd_out = STDOUT_FILENO;
    child_aux(token, *env, fd_in, fd_out, 0);
}


void	exe_one_cmd(t_token *token, t_env **env)
{
	pid_t pid;
    int status;

    pid = fork();
    if (pid < 0)
        exit_fork_pipe(FORK);
    if (pid == 0)
        child_process(token, env);
    
    waitpid(pid, &status, 0);
    
    // CORRECCIÓN: Manejar tanto terminación normal como por señal
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

    if (!token || !token->command)
    {
        if (*env)
            (*env)->last_out = 1;
        return;
    }
    fd_in = open_infile(token->infile);
    if (fd_in < 0 && token->infile) // Solo error si había redirección
    {
        (*env)->last_out = 1;
        return;
    }
    fd_out = open_outfile(token->outfile);
    if (fd_out < 0 && token->outfile) // Solo error si había redirección
    {
        if (fd_in >= 0 && fd_in != STDIN_FILENO)
            close(fd_in);
        (*env)->last_out = 1;
        return;
    }
    if (fd_in != STDIN_FILENO)
        saved_stdin = dup(STDIN_FILENO);
    if (fd_out != STDOUT_FILENO)
        saved_stdout = dup(STDOUT_FILENO);
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

