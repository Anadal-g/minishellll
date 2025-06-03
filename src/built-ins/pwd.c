/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 16:59:23 by anadal-g          #+#    #+#             */
/*   Updated: 2025/06/02 13:08:56 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int do_pwd(void)
{
    char *path;

    path = getcwd(NULL, 0);
    if (!path)
    {
        perror("minishell: pwd");
        return (1);
    }
    ft_putstr_fd(path, STDOUT_FILENO);
    ft_putstr_fd("\n", STDOUT_FILENO);
    free(path);
    return (0);
}