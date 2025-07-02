/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:11:12 by anadal-g          #+#    #+#             */
/*   Updated: 2025/07/02 13:14:31 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include "./defines.h"
# include "./structs.h"
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>

/* Global variable for signal handling */
extern int g_signal_received;

/* Main functions */
void	show_lst(t_token **stack);
void	signal_input(void);
void signal_child(void);

/*===========================================*/
/*                BUILTINS                   */
/*===========================================*/
void	select_builtin(t_token **tokens, t_env **env, char *input);
int		is_builtin(const char *command);
int		do_echo(t_token *token);
int		ft_cd(t_token *token, t_env **envp);
int		do_pwd(void);
int		do_export(t_token *token, t_env **env);
int		do_unset(t_token *token, t_env **env);
int		do_env(t_token *token, t_env *env);
int		do_exit(t_token *token, t_env **env);

/*===========================================*/
/*                   ENV                     */
/*===========================================*/
t_env	*ft_create_env_node(char *env_var);
void	ft_init_env(t_env **env_list, char **env);
t_env	*ft_new_env(char *name, char *value);
void	ft_addback_env(t_env **lst, t_env *new);
t_env	*ft_find_env(t_env *env_list, char *name);
void	ft_del_env(t_env *env_node);
char	**env_to_array(t_env *env);
void	set_shell_lvl(t_env **envp);

/*===========================================*/
/*                   EXEC                    */
/*===========================================*/
void	executor(t_token *tokens, t_env **env);
void	exe_one_cmd(t_token *token, t_env **env);
void	exe_built_ins(t_token *token, t_env **env);
void	first_child(t_token *token, t_env **env, int *fd);
void	mid_child(t_token *token, t_env **env, int *fd, int *new);
void	last_child(t_token *token, t_env **env, int *fd);
void	wait_childs(pid_t final_pid, int *last_out);
void	child_aux(t_token *token, t_env *env, int fd_in, int fd_out, int is_piped);
int		open_infile(t_iofile *infiles);
int		open_outfile(t_iofile *outfiles);
char	*heredoc(char *delimiter);
enum e_iotype	get_redirection_type(char *token);
void	add_iofile(t_iofile **list, char *filename, enum e_iotype type);
char	*get_path(char *cmd, t_env **env);
void	setup_child_io(int fd_in, int fd_out);
char	*handle_command_path(t_token *token, t_env *env, char ***env_array);
void	exit_fork_pipe(int type);
int		validate_token(t_token *token);

/*===========================================*/
/*               PARSING                     */
/*===========================================*/
void	quotes_check_in_token(char *token, int *in_quotes);
int		quotes_checker(t_token *token);
int		quotes_handler(t_token **token, char *input);
void	quotes_remover(char *input);
char	*quote_joiner(char **tokens);
int		quote_equal(char c);
char	**quote_command_split(char *str);
void	add_node_tokens(t_token **stack_tokens, char **splited_tokens);
void	create_tokens(char *input, t_token **tokens);
void	show_error(char *str, char *cmd_file);
void	show_error_reverse(char *cmd_file, char *str);
char	*get_variable_name(char **str);
void	append_expanded(char **result, size_t *result_len, char *var_name, t_env *env);
void	append_other_characters(char **result, size_t *result_len, char c);
char	*expand_variable(char *str, t_env *env);
void	expander(char **tokens, t_env *env);
void	free_list(t_token **stack);
void	free_tokens(t_token **tokens);
void	free_env(t_env **env);
void	free_iofile(t_iofile *iofile);
void	lexerize_process(t_token *aux, t_env *env);
void	lexerize(t_token **tokens, t_env *env);
void	jump_character(char *str, int *counter, char c, int flag);
void	read_till_character(char *str, int *start, int *counter, char c);
int		write_command(char **r, char *str, char c);
int		command_counter(char *str, char c);
char	**command_spliter(char const *s, char c);
t_token	*last_node(t_token *lst);
void	add_node_back(t_token **stack, t_token *new);
t_token	*create_node(int id, char *command);
char	**redir_divisor(char const *s);
void	remove_redirection_tokens(char **tokens);
void	parse_redirections(t_token *token);
int		redir_counter(char *str);
int		redir_command_spliter(char **r, char *str);
void	detect_redirections(t_token *token);

/*===========================================*/
/*                SIGNALS                    */
/*===========================================*/
void	crtl_c(int sign);
void	signal_input(void);

/*===========================================*/
/*                UTILS                      */
/*===========================================*/
int		character_finder(char c, char to_find);
int		is_redir(char *str, int i);
char	*ft_strndup(const char *s, size_t n);
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);
int		validate_pipe_syntax(char *input);
int		validate_input_syntax(char *input);

#endif
