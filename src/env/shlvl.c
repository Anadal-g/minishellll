/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:58:11 by anadal-g          #+#    #+#             */
/*   Updated: 2025/06/25 13:49:20 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void set_shell_lvl(t_env **envp)
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
		{
			perror("Error al asignar memoria para SHLVL");
			return;
		}
		free(data->value);
		data->value = aux;
	}
	else
	{
		data = ft_new_env("SHLVL", "1");
		if (!data)
		{
			perror("Memory Error");
			return;
		}
		ft_addback_env(envp, data);
	}
}