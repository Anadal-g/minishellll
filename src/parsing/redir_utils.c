/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 13:53:36 by anadal-g          #+#    #+#             */
/*   Updated: 2025/06/25 13:53:39 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void remove_redirection_tokens(char **tokens)
{
    int i = 0;
    int j;
    
    if (!tokens)
        return;
        
    while (tokens[i])
    {
        if (ft_strcmp(tokens[i], "<") == 0 || ft_strcmp(tokens[i], "<<") == 0 ||
            ft_strcmp(tokens[i], ">") == 0 || ft_strcmp(tokens[i], ">>") == 0)
        {
            free(tokens[i]);
            if (tokens[i + 1])
                free(tokens[i + 1]);
            j = i;
            while (tokens[j + 2])
            {
                tokens[j] = tokens[j + 2];
                j++;
            }
            tokens[j] = NULL;
            if (tokens[j + 1])
                tokens[j + 1] = NULL;
        }
        else
            i++;
    }
}

void parse_redirections(t_token *token)
{
    if (!token)
        return;
        
    detect_redirections(token);
    remove_redirection_tokens(token->tokens);
}
