/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 16:59:23 by anadal-g          #+#    #+#             */
/*   Updated: 2025/06/02 13:08:38 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int is_numeric(char *str)
{
    int i = 0;
    
    if (!str || !*str)
        return (0);
    
    if (str[i] == '+' || str[i] == '-')
        i++;
    
    if (!str[i])  // Solo signo sin número
        return (0);
    
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}

int do_exit(t_token *token, char *input)
{
    int exit_code = 0;
    
    ft_putstr_fd("exit\n", STDERR_FILENO);
    
    if (token->tokens[1])
    {
        // Verificar si hay más de un argumento
        if (token->tokens[2])
        {
            ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
            return (1);  // No salir, solo retornar error
        }
        
        // Verificar si el argumento es numérico
        if (!is_numeric(token->tokens[1]))
        {
            ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
            ft_putstr_fd(token->tokens[1], STDERR_FILENO);
            ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
            exit(2);
        }
        
        exit_code = ft_atoi(token->tokens[1]);
    }
    
    // Limpiar memoria antes de salir
    if (input)
        free(input);
    
    exit(exit_code & 255);  // Solo los últimos 8 bits
}