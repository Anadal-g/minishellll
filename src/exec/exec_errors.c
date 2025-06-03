/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:23:55 by anadal-g          #+#    #+#             */
/*   Updated: 2025/03/27 11:52:18 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_fork_pipe(int type)
{
	if (type == PIPE)
		ft_putstr_fd("minishell: error creating pipe\n", STDERR_FILENO);
	else if (type == FORK)
		ft_putstr_fd("minishell: fork error\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}
