/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 16:59:23 by anadal-g          #+#    #+#             */
/*   Updated: 2025/06/02 13:12:22 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


static int is_valid_var_name(char *name)
{
    int i;

    if (!name || !*name)
        return (0);
    if (!ft_isalpha(name[0]) && name[0] != '_')
        return (0);
    i = 1;
    while (name[i] && name[i] != '=')
    {
        if (!ft_isalnum(name[i]) && name[i] != '_')
            return (0);
        i++;
    }
    return (1);
}

static void print_sorted_env(t_env *env)
{
    t_env **env_array;
    t_env *temp;
    int count;
    int i;
    int j;

    count = 0;
    temp = env;
    while (temp)
    {
        count++;
        temp = temp->next;
    }
    
    if (count == 0)
        return;
    
    env_array = (t_env **)malloc(sizeof(t_env *) * count);
    if (!env_array)
        return ;
    
    temp = env;
    i = 0;
    while (temp)
    {
        env_array[i++] = temp;
        temp = temp->next;
    }
    
    // Ordenamiento burbuja
    i = 0;
    while (i < count - 1)
    {
        j = 0;
        while (j < count - i - 1)
        {
            if (ft_strcmp(env_array[j]->name, env_array[j + 1]->name) > 0)
            {
                temp = env_array[j];
                env_array[j] = env_array[j + 1];
                env_array[j + 1] = temp;
            }
            j++;
        }
        i++;
    }

    i = 0;
    while (i < count)
    {
        ft_putstr_fd("declare -x ", STDOUT_FILENO);
        ft_putstr_fd(env_array[i]->name, STDOUT_FILENO);
        if (env_array[i]->value)
        {
            ft_putstr_fd("=\"", STDOUT_FILENO);
            ft_putstr_fd(env_array[i]->value, STDOUT_FILENO);
            ft_putstr_fd("\"", STDOUT_FILENO);
        }
        ft_putstr_fd("\n", STDOUT_FILENO);
        i++;
    }

    free(env_array);
}

static void add_or_update_env(t_env **env, char *name, char *value)
{
    t_env *var;

    var = ft_find_env(*env, name);
    if (var)
    {
        if (value)
        {
            free(var->value);
            var->value = ft_strdup(value);
        }
    }
    else
    {
        var = ft_new_env(name, value);
        if (var)
        {
            var->next = *env;
            *env = var;
        }
    }
}

static int process_export_arg(char *arg, t_env **env)
{
    char *equal_sign;
    char *name;
    char *value;

    if (!is_valid_var_name(arg))
    {
        ft_putstr_fd("minishell: export: `", STDERR_FILENO);
        ft_putstr_fd(arg, STDERR_FILENO);
        ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
        return (1);
    }

    equal_sign = ft_strchr(arg, '=');
    if (equal_sign)
    {
        name = ft_substr(arg, 0, equal_sign - arg);
        value = ft_strdup(equal_sign + 1);
        if (!name || !value)
        {
            free(name);
            free(value);
            ft_putstr_fd("minishell: export: memory allocation error\n", STDERR_FILENO);
            return (1);
        }

        add_or_update_env(env, name, value);
        free(name);
        free(value);
    }
    else
    {
        if (!ft_find_env(*env, arg))
            add_or_update_env(env, arg, NULL);
    }

    return (0);
}

int do_export(t_token *token, t_env **env)
{
    int i;
    int exit_status;

    exit_status = 0;
    if (!token->tokens[1])
    {
        print_sorted_env(*env);
        return (0);
    }
    
    i = 1;
    while (token->tokens[i])
    {
        if (process_export_arg(token->tokens[i], env))
            exit_status = 1;
        i++;
    }
    
    return (exit_status);
}
