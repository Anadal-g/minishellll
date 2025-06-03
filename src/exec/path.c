/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:37:44 by anadal-g          #+#    #+#             */
/*   Updated: 2025/03/28 10:56:39 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_full_path(char *cmd)
{
	int	i;

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

	i = 0;
	while (path_list && path_list[i])
	{
		tmp = ft_strjoin(path_list[i], "/");
		if (!tmp)
			return (NULL);
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!path)
			return (NULL);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

static char	**get_path_list(t_env **env)
{
	t_env	*current;
	char	**path_list;

	current = *env;
	while (current)
	{
		if (ft_strcmp(current->name, "PATH") == 0)
		{
			path_list = ft_split(current->value, ':');
			return (path_list);
		}
		current = current->next;
	}
	return (NULL);
}

char *get_path(char *cmd, t_env **env)
{
    char **path_list;
    char *path_cmd;
    int i;

    if (!cmd || !*cmd)
        return (NULL);
    if (is_full_path(cmd))
    {
        if (access(cmd, F_OK) == 0)
            return (ft_strdup(cmd));
        return (NULL);
    }
    path_list = get_path_list(env);
    path_cmd = search_in_path(cmd, path_list);
    // Limpieza de path_list
    if (path_list)
    {
        i = 0;
        while (path_list[i])
            free(path_list[i++]);
        free(path_list);
    }
    return (path_cmd);
}
