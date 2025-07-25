/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinamc <carolinamc@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:29:16 by mmendiol          #+#    #+#             */
/*   Updated: 2025/07/24 20:20:17 by carolinamc       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_token	t_token;
typedef struct s_env	t_env;
typedef struct s_iofile	t_iofile;

enum e_iotype
{
	INFILE,
	HEREDOC,
	APPEND,
	TRUNC,
};

struct s_iofile
{
	char				*name;
	int					fd;
	enum e_iotype		type;
	struct s_iofile		*prev;
	struct s_iofile		*next;
};

struct s_token
{
	int					id;
	char				*command;
	char				**tokens;
	t_iofile			*infile;
	t_iofile			*outfile;
	t_token				*prev;
	t_token				*next;
};

struct s_env
{
	char				*name;
	char				*value;
	t_env				*prev;
	t_env				*next;
	int					last_out;
};

typedef struct s_pipe_fds
{
	int	prev_fd[2];
	int	curr_fd[2];
}	t_pipe_fds;

typedef struct s_child_io_context
{
	int	fd_in;
	int	fd_out;
	int	prev_fd[2];
	int	curr_fd[2];
	int	is_last;
}	t_child_io_context;

#endif
