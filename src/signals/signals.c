/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinamc <carolinamc@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:10:05 by anadal-g          #+#    #+#             */
/*   Updated: 2025/11/03 11:23:39 by carolinamc       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

void	crtl_c(int sign)
{
	(void)sign;
	g_signal_received = SIGINT;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_input(void)
{
	signal(SIGINT, &crtl_c);
	signal(SIGQUIT, SIG_IGN);
}
