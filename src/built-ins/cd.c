/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 12:19:17 by anadal-g          #+#    #+#             */
/*   Updated: 2025/06/02 13:09:43 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
void ft_set_env(t_env **env, t_env *new_var)
{
    t_env *tmp = *env;

    while (tmp)
    {
        if (ft_strcmp(tmp->name, new_var->name) == 0)
        {
            free(tmp->value);
            tmp->value = ft_strdup(new_var->value);
            free(new_var->name);
            free(new_var->value);
            free(new_var);
            return;
        }
        tmp = tmp->next;
    }
    // si no existe, añadir al final
    new_var->next = *env;
    *env = new_var;
}

char *get_env_value(char *name, t_env *envp)
{
    while (envp)
    {
        if (ft_strcmp(envp->name, name) == 0)
            return (envp->value);
        envp = envp->next;
    }
    return (NULL);
}

int change_directory(const char *path)
{
    if (chdir(path) == -1)
    {
        ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
        perror(path);
        return (-1);
    }
    return (0);
}

int handle_special_cases(t_env *envp, char **current, t_token *token)
{
    char *home;
    char *actual_path;

    if (!token->tokens[1] || !ft_strncmp(token->tokens[1], "--", 2))
    {
        home = get_env_value("HOME", envp);
        if (!home)
        {
            ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
            return (-1);
        }
        if (change_directory(home) == -1)
            return (-1);
        *current = ft_strdup(home);
        return (1);
    }
    else if (!ft_strncmp(token->tokens[1], "-", 2))
    {
        actual_path = get_env_value("OLDPWD", envp);
        if (!actual_path)
        {
            ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDERR_FILENO);
            return (-1);
        }
        if (change_directory(actual_path) == -1)
            return (-1);
        ft_putstr_fd(actual_path, STDOUT_FILENO);
        ft_putchar_fd('\n', STDOUT_FILENO);
        *current = ft_strdup(actual_path);
        return (1);
    }
    return (0);
}

int ft_cd(t_token *token, t_env **env)
{
    char *cur_path = NULL;
    char *old_path;
    int result;
    t_env *oldpwd_node;
    t_env *pwd_node;

    old_path = getcwd(NULL, 0);
    if (!old_path)
    {
        perror("minishell: cd");
        return (1);
    }

    result = handle_special_cases(*env, &cur_path, token);
    if (result == -1)
    {
        free(old_path);
        return (1);
    }
    else if (result == 1)
    {
        oldpwd_node = ft_new_env("OLDPWD", old_path);
        if (oldpwd_node)
            ft_set_env(env, oldpwd_node);
        
        cur_path = getcwd(NULL, 0);
        if (cur_path)
        {
            pwd_node = ft_new_env("PWD", cur_path);
            if (pwd_node)
                ft_set_env(env, pwd_node);
            free(cur_path);
        }
        free(old_path);
        return (0);
    }

    // Verificar si hay demasiados argumentos
    if (token->tokens[2])
    {
        ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
        free(old_path);
        return (1);
    }

    if (change_directory(token->tokens[1]) == -1)
    {
        free(old_path);
        return (1);
    }

    oldpwd_node = ft_new_env("OLDPWD", old_path);
    if (oldpwd_node)
        ft_set_env(env, oldpwd_node);
    
    cur_path = getcwd(NULL, 0);
    if (cur_path)
    {
        pwd_node = ft_new_env("PWD", cur_path);
        if (pwd_node)
            ft_set_env(env, pwd_node);
        free(cur_path);
    }
    free(old_path);
    return (0);
}