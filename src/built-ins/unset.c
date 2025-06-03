// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   unset.c                                            :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/05/11 21:01:25 by mmendiol          #+#    #+#             */
// /*   Updated: 2025/04/22 11:12:59 by anadal-g         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "../../includes/minishell.h"

static int is_valid_var_name_unset(char *name)
{
    int i;

    if (!name || !*name)
        return (0);
    if (!ft_isalpha(name[0]) && name[0] != '_')
        return (0);
    i = 1;
    while (name[i])
    {
        if (!ft_isalnum(name[i]) && name[i] != '_')
            return (0);
        i++;
    }
    return (1);
}

static void remove_env_node(t_env **env, t_env *node)
{
    t_env *current;
    t_env *prev;

    if (!env || !*env || !node)
        return ;
    
    if (*env == node)
    {
        *env = node->next;
        ft_del_env(node);
        return ;
    }
    
    prev = NULL;
    current = *env;
    while (current && current != node)
    {
        prev = current;
        current = current->next;
    }
    
    if (current)
    {
        prev->next = current->next;
        ft_del_env(current);
    }
}

int do_unset(t_token *token, t_env **env)
{
    int i;
    t_env *result;
    int exit_status;

    exit_status = 0;
    i = 1;
    
    if (!token->tokens[i])
        return (0);
    
    while (token->tokens[i])
    {
        if (!is_valid_var_name_unset(token->tokens[i]))
        {
            ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
            ft_putstr_fd(token->tokens[i], STDERR_FILENO);
            ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
            exit_status = 1;
            i++;
            continue;
        }
        
        result = ft_find_env(*env, token->tokens[i]);
        if (result)
            remove_env_node(env, result);
            
        i++;
    }    
    return (exit_status);
}
