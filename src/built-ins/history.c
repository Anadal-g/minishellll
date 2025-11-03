/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinamc <carolinamc@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:05:02 by mmendiol          #+#    #+#             */
/*   Updated: 2025/11/03 11:21:58 by carolinamc       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../includes/minishell.h"

// int show_history(t_token *token)
// {
//     HIST_ENTRY **history;
//     int width;
//     int i;

//     // history no debe aceptar argumentos
//     if (token->tokens[1])
//     {
//         ft_putstr_fd("minishell: history: too many arguments\n", STDERR_FILENO);
//         return (1);
//     }

//     width = 6;
//     history = history_list();
//     if (history)
//     {
//         i = -1;
//         while (history[++i])
//         {
//             ft_printf("%*d  %s\n", width, i + history_base, history[i]->line);
//         }
//     }
//     return (0);
// }