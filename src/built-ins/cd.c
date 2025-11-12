/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 12:19:17 by anadal-g          #+#    #+#             */
/*   Updated: 2025/11/12 10:35:32 by anadal-g         ###   ########.fr       */
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

static char	*resolve_cd_path(t_token *token, t_env **envp)
{
	t_env	*env;

	if (!token->tokens[1])
	{
		env = ft_find_env(*envp, "HOME");
		if (!env || !env->value)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
			return (NULL);
		}
		return (ft_strdup(env->value));
	}
	if (ft_strcmp(token->tokens[1], "-") == 0)
	{
		env = ft_find_env(*envp, "OLDPWD");
		if (!env || !env->value)
		{
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDERR_FILENO);
			return (NULL);
		}
		ft_putendl_fd(env->value, STDOUT_FILENO);
		return (ft_strdup(env->value));
	}
	return (ft_strdup(token->tokens[1]));
}

static int	cd_error(char *path, char *old_pwd)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	free(path);
	free(old_pwd);
	return (1);
}

int	ft_cd(t_token *token, t_env **envp)
{
	char	*path;
	char	*old_pwd;
	char	*new_pwd;

	if (!token || !token->tokens)
		return (1);
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (1);
	path = resolve_cd_path(token, envp);
	if (!path)
		return (free(old_pwd), 1);
	if (chdir(path) != 0)
		return (cd_error(path, old_pwd));
	new_pwd = getcwd(NULL, 0);
	if (new_pwd)
	{
		update_pwd_env(envp, old_pwd, new_pwd);
		free(new_pwd);
	}
	free(path);
	free(old_pwd);
	return (0);
}
