/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 16:58:03 by anadal-g          #+#    #+#             */
/*   Updated: 2025/06/02 13:09:08 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


int do_env(t_token *token, t_env *env)
{
    // env no debe aceptar argumentos según el subject
    if (token->tokens[1])
    {
        ft_putstr_fd("minishell: env: too many arguments\n", STDERR_FILENO);
        return (1);
    }
    
    while (env)
    {
        if (env->value && ft_strcmp(env->value, ""))
        {
            ft_putstr_fd(env->name, STDOUT_FILENO);
            ft_putstr_fd("=", STDOUT_FILENO);
            ft_putstr_fd(env->value, STDOUT_FILENO);
            ft_putstr_fd("\n", STDOUT_FILENO);
        }
        env = env->next;
    }
    return (0);
}