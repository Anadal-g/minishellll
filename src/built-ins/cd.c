/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinamc <carolinamc@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 12:19:17 by anadal-g          #+#    #+#             */
/*   Updated: 2025/07/15 13:27:59 by carolinamc       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	update_pwd_env(t_env **env, char *old_pwd, char *new_pwd)
{
	t_env	*pwd_env;
	t_env	*oldpwd_env;

	oldpwd_env = ft_find_env(*env, "OLDPWD");
	if (oldpwd_env)
	{
		free(oldpwd_env->value);
		oldpwd_env->value = ft_strdup(old_pwd);
	}
	pwd_env = ft_find_env(*env, "PWD");
	if (pwd_env)
	{
		free(pwd_env->value);
		pwd_env->value = ft_strdup(new_pwd);
	}
}

int	handle_cd_path(char *path, char *old_pwd, t_env **envp)
{
	char	*new_pwd;

	if (chdir(path) != 0)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		free(old_pwd);
		return (1);
	}
	new_pwd = getcwd(NULL, 0);
	if (new_pwd)
	{
		update_pwd_env(envp, old_pwd, new_pwd);
		free(new_pwd);
	}
	free(old_pwd);
	return (0);
}

int	ft_cd(t_token *token, t_env **envp)
{
	char	*path;
	char	*old_pwd;
	t_env	*home_env;

	if (!token || !token->tokens)
		return (1);
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (1);
	if (!token->tokens[1])
	{
		home_env = ft_find_env(*envp, "HOME");
		if (!home_env || !home_env->value)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
			free(old_pwd);
			return (1);
		}
		path = home_env->value;
	}
	else
		path = token->tokens[1];
	return (handle_cd_path(path, old_pwd, envp));
}
