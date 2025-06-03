/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:29:16 by mmendiol          #+#    #+#             */
/*   Updated: 2025/06/03 12:46:47 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_token	t_token;
typedef struct s_env	t_env;
typedef struct s_iofile	t_iofile;
enum					e_iotype;

enum					e_iotype
{
	INFILE,
	HEREDOC,
	APPEND,
	TRUNC,
};

struct					s_iofile
{
	char				*name;
	int					fd;
	enum e_iotype		type;
	struct s_iofile		*prev;
	struct s_iofile		*next;
};

struct					s_token
{
	int					id;
	char				*command;
	char				**tokens;
	t_iofile			*infile;
	t_iofile			*outfile;
	t_token				*prev;
	t_token				*next;
};

struct					s_env
{
	char				*name;
	char				*value;
	t_env				*prev;
	t_env				*next;
	t_env				*env_list;
	int             last_out;
};

#endif
