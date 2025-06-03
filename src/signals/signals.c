/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:10:05 by anadal-g          #+#    #+#             */
/*   Updated: 2024/10/10 15:56:44 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	crtl_c(int sign)
{
	(void)sign;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	write(1, "\n", 1);
}

void	signal_input(void)
{
	signal(SIGINT, &crtl_c);
	signal(SIGQUIT, SIG_IGN);
}
