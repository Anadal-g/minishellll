/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:24:03 by anadal-g          #+#    #+#             */
/*   Updated: 2025/11/02 19:07:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	show_error(char *str, char *cmd_file)
{
	char	*msg;

	msg = ft_strjoin(str, cmd_file);
	if (msg)
	{
		ft_putstr_fd(msg, 2);
		ft_putstr_fd("\n", 2);
		free(msg);
	}
}

void	show_error_reverse(char *cmd_file, char *str)
{
	char	*msg;

	msg = ft_strjoin(cmd_file, str);
	if (msg)
	{
		ft_putstr_fd(msg, 2);
		ft_putstr_fd("\n", 2);
		free(msg);
	}
}
