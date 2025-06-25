/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:14:11 by anadal-g          #+#    #+#             */
/*   Updated: 2025/06/25 13:48:51 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int validate_token(t_token *token)
{
	if (!token)
		return (0);
	if (!token->tokens)
		return (0);
	if (!token->tokens[0])
		return (0);
	if (!token->command)
		return (0);
	return (1);
}