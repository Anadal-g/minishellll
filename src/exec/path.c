/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:37:44 by anadal-g          #+#    #+#             */
/*   Updated: 2025/10/28 20:00:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char *search_in_path(char *cmd, char **path_list)
{
	char *path;
	int i;

	if (!cmd || !*cmd || !path_list)
		return (NULL);
	i = 0;
	while (path_list[i])
	{
		if (!path_list[i] || !*path_list[i])
		{
			i++;
			continue;
		}
		path = build_full_path(path_list[i], cmd);
		if (!path)
			return (NULL);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

static char **get_path_list(t_env **env)
{
	t_env *current;

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

static int is_empty_command(char *cmd)
{
	int i;

	i = 0;
	while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '\t'))
		i++;
	if (!cmd[i])
		return (1);
	return (0);
}

static void free_path_list(char **path_list)
{
	int i;

	i = 0;
	while (path_list[i])
	{
		free(path_list[i]);
		i++;
	}
	free(path_list);
}

char *get_path(char *cmd, t_env **env)
{
	char **path_list;
	char *path_cmd;

	if (!cmd || !*cmd || !env || !*env)
		return (NULL);
	if (is_empty_command(cmd))
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
	free_path_list(path_list);
	return (path_cmd);
}
