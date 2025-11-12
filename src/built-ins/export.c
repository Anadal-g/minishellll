/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 16:59:23 by anadal-g          #+#    #+#             */
/*   Updated: 2025/11/12 11:39:40 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	handle_existing_env(t_env *existing, char *value, char *name)
{
	if (existing && value)
	{
		free(existing->value);
		existing->value = value;
		free(name);
		return (1);
	}
	return (0);
}

static int	parse_export_arg(char *arg, t_pair *pair)
{
	char	*eq;

	eq = ft_strchr(arg, '=');
	if (eq)
	{
		pair->name = ft_substr(arg, 0, eq - arg);
		pair->value = ft_strdup(eq + 1);
	}
	else
	{
		pair->name = ft_strdup(arg);
		pair->value = NULL;
	}
	if (!pair->name)
		return (1);
	return (0);
}

static int	handle_invalid_id(char *arg, t_pair *pair)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	free(pair->name);
	free(pair->value);
	return (1);
}

static int	export_variable(char *arg, t_env **env)
{
	t_pair	pair;
	t_env	*existing;

	if (parse_export_arg(arg, &pair))
		return (1);
	if (!is_valid_identifier(pair.name))
		return (handle_invalid_id(arg, &pair));
	existing = ft_find_env(*env, pair.name);
	if (handle_existing_env(existing, pair.value, pair.name))
		return (0);
	return (create_new_env(pair.name, pair.value, env));
}

int	do_export(t_token *token, t_env **env)
{
	int	i;
	int	status;

	if (!token || !token->tokens || !env)
		return (1);
	if (!token->tokens[1])
		return (print_export_env(*env), 0);
	status = 0;
	i = 1;
	while (token->tokens[i])
	{
		if (export_variable(token->tokens[i], env) != 0)
			status = 1;
		i++;
	}
	return (status);
}
