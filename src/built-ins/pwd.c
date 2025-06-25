/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 16:59:23 by anadal-g          #+#    #+#             */
/*   Updated: 2025/06/25 13:19:47 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int do_pwd(void)
{
	char *pwd;
	
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("minishell: pwd");
		return (1);
	}
	
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}
