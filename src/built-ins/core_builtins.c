/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 21:01:25 by mmendiol          #+#    #+#             */
/*   Updated: 2025/11/11 11:31:42 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(const char *command)
{
	if (!command)
		return (0);
	if (ft_strcmp(command, ECHO_TXT) == 0)
		return (1);
	if (ft_strcmp(command, CD_TXT) == 0)
		return (1);
	if (ft_strcmp(command, PWD_TXT) == 0)
		return (1);
	if (ft_strcmp(command, EXPORT_TXT) == 0)
		return (1);
	if (ft_strcmp(command, UNSET_TXT) == 0)
		return (1);
	if (ft_strcmp(command, ENV_TXT) == 0)
		return (1);
	if (ft_strcmp(command, EXIT_TXT) == 0)
		return (1);
	return (0);
}

void	select_builtin(t_token **tokens, t_env **env, char *input)
{
	int	exit_status;

	(void)input;
	if (!tokens || !*tokens || !(*tokens)->tokens || !(*tokens)->tokens[0])
		return ;
	if (ft_strcmp((*tokens)->tokens[0], ECHO_TXT) == 0)
		exit_status = do_echo(*tokens);
	else if (ft_strcmp((*tokens)->tokens[0], CD_TXT) == 0)
		exit_status = ft_cd(*tokens, env);
	else if (ft_strcmp((*tokens)->tokens[0], PWD_TXT) == 0)
		exit_status = do_pwd();
	else if (ft_strcmp((*tokens)->tokens[0], EXPORT_TXT) == 0)
		exit_status = do_export(*tokens, env);
	else if (ft_strcmp((*tokens)->tokens[0], UNSET_TXT) == 0)
		exit_status = do_unset(*tokens, env);
	else if (ft_strcmp((*tokens)->tokens[0], ENV_TXT) == 0)
		exit_status = do_env(*tokens, *env);
	else if (ft_strcmp((*tokens)->tokens[0], EXIT_TXT) == 0)
		exit_status = do_exit(*tokens, env);
	else
		exit_status = 127;
	if (*env)
		(*env)->last_out = exit_status;
}
