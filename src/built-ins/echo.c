/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:20:05 by mmendiol          #+#    #+#             */
/*   Updated: 2025/06/02 13:08:22 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#include "../../includes/minishell.h"

static int is_valid_n_flag(char *arg)
{
    int i;
    
    if (!arg || arg[0] != '-' || arg[1] != 'n')
        return (0);
    
    i = 2;
    while (arg[i])
    {
        if (arg[i] != 'n')
            return (0);
        i++;
    }
    return (1);
}

int do_echo(t_token *token)
{
    int i = 1;
    int newline = 1;  // Por defecto, imprimir newline
    
    if (!token || !token->tokens)
        return (1);
    
    // Verificar si hay flags -n
    while (token->tokens[i] && is_valid_n_flag(token->tokens[i]))
    {
        newline = 0;
        i++;
    }
    
    // Imprimir argumentos
    while (token->tokens[i])
    {
        ft_putstr_fd(token->tokens[i], STDOUT_FILENO);
        if (token->tokens[i + 1])
            ft_putstr_fd(" ", STDOUT_FILENO);
        i++;
    }
    
    if (newline)
        ft_putstr_fd("\n", STDOUT_FILENO);
    
    return (0);
}