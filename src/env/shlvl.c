/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:58:11 by anadal-g          #+#    #+#             */
/*   Updated: 2024/10/25 17:27:32 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*void set_shell_lvl_aument(t_env **envp, t_env *data)
{
	int		nb;
	char	*aux;
	t_env	*data;
	int		nb;
	char	*aux;

	nb = ft_atoi(data->value); //Pasamos el valor de la cadena a un entero
	aux = ft_itoa(nb + 1);
		//Incremmentamos el valor de nb y lo reconvertimos a cadena
	if (aux == NULL)
		perror("Error al asignar memori para SHLVL");
			//Error si no se ha podido asignar memoria correctamente
	data = ft_new_env("SHLVL", aux);
		// Crea una nueva variable con el valor de aux
	if (!data) //Si no se puede crear nuevo env
	{
		free(aux);
		perror_error("Memory Error");
	}
	ft_set_env(envp, data); //Actualizamos con la nueva variable
	free(aux);
}*/
void	set_shell_lvl(t_env **envp)
{
	t_env	*data;
	int		nb;
	char	*aux;

	data = ft_find_env(*envp, "SHLVL");
	if (data && data->value)
	{
		nb = ft_atoi(data->value);
		aux = ft_itoa(nb + 1);
		if (aux == NULL)
			perror("Error al asignar memoria para SHLVL");
		data->value = aux;
		free(aux);
	}
	else
	{
		data = ft_new_env("SHLVL", "1");
		if (!data)
		{
			perror_error("Memory Error");
			exit(EXIT_FAILURE);
		}
		ft_addback_env(envp, data);
	}
}
