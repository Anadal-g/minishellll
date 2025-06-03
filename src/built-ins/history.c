/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:05:02 by mmendiol          #+#    #+#             */
/*   Updated: 2025/06/02 13:09:19 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int show_history(t_token *token)
{
    HIST_ENTRY **history;
    int width;
    int i;

    // history no debe aceptar argumentos
    if (token->tokens[1])
    {
        ft_putstr_fd("minishell: history: too many arguments\n", STDERR_FILENO);
        return (1);
    }

    width = 6;
    history = history_list();
    if (history)
    {
        i = -1;
        while (history[++i])
        {
            ft_printf("%*d  %s\n", width, i + history_base, history[i]->line);
        }
    }
    return (0);
}