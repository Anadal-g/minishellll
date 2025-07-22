/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinamc <carolinamc@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:37:44 by anadal-g          #+#    #+#             */
/*   Updated: 2025/07/22 13:29:33 by carolinamc       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_full_path(char *cmd)
{
	int	i;

	if (!cmd)
		return (0);
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

static char	*search_in_path(char *cmd, char **path_list)
{
	char	*path;
	char	*tmp;
	int		i;

	if (!cmd || !path_list)
		return (NULL);
	i = 0;
	while (path_list[i])
	{
		tmp = ft_strjoin(path_list[i], "/");
		if (!tmp)
			return (NULL);
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!path)
			return (NULL);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

static char	**get_path_list(t_env **env)
{
	t_env	*current;

	if (!env || !*env)
		return (NULL);
	current = *env;
	while (current)
	{
		if (current->name && ft_strcmp(current->name, "PATH") == 0)
		{
			if (current->value && *current->value)
				return (ft_split(current->value, ':'));
			return (NULL);
		}
		current = current->next;
	}
	return (NULL);
}

char	*get_path(char *cmd, t_env **env)
{
	char	**path_list;
	char	*path_cmd;
	int		i;

	if (!cmd || !*cmd || !env || !*env)
		return (NULL);
	if (is_full_path(cmd))
	{
		if (access(cmd, F_OK) == 0 && access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path_list = get_path_list(env);
	if (!path_list)
		return (NULL);
	path_cmd = search_in_path(cmd, path_list);
	i = 0;
	while (path_list[i])
		free(path_list[i++]);
	free(path_list);
	return (path_cmd);
}
