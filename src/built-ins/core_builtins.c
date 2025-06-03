/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 21:01:25 by mmendiol          #+#    #+#             */
/*   Updated: 2025/06/02 13:14:26 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


int is_builtin(const char *command)
{
    if (!command)
        return (0);
    
    return (!ft_strcmp(command, "cd") ||
           !ft_strcmp(command, "echo") ||
           !ft_strcmp(command, "exit") ||
           !ft_strcmp(command, "export") ||
           !ft_strcmp(command, "unset") ||
           !ft_strcmp(command, "env") ||
           !ft_strcmp(command, "pwd") ||
           !ft_strcmp(command, "history"));
}

void select_builtin(t_token **tokens, t_env **env, char *input)
{
    t_token *token;
    int exit_code = 0;

    if (!tokens || !*tokens)
        return ;
    
    token = *tokens;
    
    if (ft_strcmp(token->command, "exit") == 0)
        exit_code = do_exit(token, input);
    else if (ft_strcmp(token->command, "echo") == 0)
        exit_code = do_echo(token);
    else if (ft_strcmp(token->command, "cd") == 0)
        exit_code = ft_cd(token, env);
    else if (ft_strcmp(token->command, "pwd") == 0)
        exit_code = do_pwd();
    else if (ft_strcmp(token->command, "export") == 0)
        exit_code = do_export(token, env);
    else if (ft_strcmp(token->command, "unset") == 0)
        exit_code = do_unset(token, env);
    else if (ft_strcmp(token->command, "env") == 0)
        exit_code = do_env(token, *env);
    else if (ft_strcmp(token->command, "history") == 0)
        exit_code = show_history(token);
    if (*env)
        (*env)->last_out = exit_code;
}
