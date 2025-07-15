/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_childs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinamc <carolinamc@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:28:31 by anadal-g          #+#    #+#             */
/*   Updated: 2025/07/15 17:15:38 by carolinamc       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static void	execute_and_cleanup(char *path, char **tokens, char **env_array)
// {
// 	if (execve(path, tokens, env_array) == -1)
// 	{
// 		perror_error("Error al ejecutar el comando");
// 		free_matrix(env_array);
// 		free(path);
// 		exit(EXIT_FAILURE);
// 	}
// 	free_matrix(env_array);
// 	free(path);
// }

static void setup_last_child(t_token *token, t_env *env, int fd_in, int fd_out)
{
    // CORRECCIÓN: Usar child_aux en lugar de código duplicado
    child_aux(token, env, fd_in, fd_out, 1); // 1 = está en pipe
}

void	last_child(t_token *token, t_env **env, int *fd)
{
	pid_t pid;
	int fd_in;
	int fd_out;

	pid = fork();
	if (pid == -1)
	{
		perror("Error en fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		close(fd[1]); // Cerramos el extremo de escritura del pipe
		
		fd_in = open_infile(token->infile);
		if (fd_in < 0)
			fd_in = fd[0]; // Si no hay redirección de entrada, usamos el pipe
		else
			close(fd[0]); // Si hay redirección, cerramos el pipe
			
		fd_out = open_outfile(token->outfile);
		if (fd_out < 0)
			fd_out = STDOUT_FILENO; // Si no hay redirección de salida, usamos stdout
			
		setup_last_child(token, *env, fd_in, fd_out);
	}
	
	// En el proceso padre
	close(fd[0]);
	close(fd[1]);
}
