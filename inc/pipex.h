/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 09:29:26 by toshota           #+#    #+#             */
/*   Updated: 2023/12/12 15:08:30 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "builtin.h"
# include "define.h"
# include "libft.h"
# include <stdio.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>

# define HERE_DOC_FILE_PATH "/tmp/here_doc"
# define INFILE 0
# define INFILE_HERE_DOC 1
# define OUTFILE_OVER_WRITING 2
# define OUTFILE_APEND 3
# define NOT_SPECIFIED 0
# define NOT_FOUND -1
# define IS_A_DIRECTORY -2
# define IS_DOT -3

int		open_file(char *file, int file_type);
bool	close_pipe(int *pipe_fd);
int		free_tab(char *ptr);
void	all_free_tab(char **ptr);
void	all_free_int(int **ptr);
size_t	strlen_until_c(char *str, char c);
void	*check_malloc(void *ptr);
bool	check_getenv(char *ptr);
bool	check_open(int fd, char *file);
bool	check_close(int ret);
bool	check_pipe(int ret);
bool	check_fork(pid_t child_pid);
bool	check_dup(int ret);
bool	check_execve(int ret, char *cmd);
bool	check_exec_builtin(int ret, char *cmd);
bool	check_wait(int ret);
bool	check_unlink(int ret);
bool	is_path_found(char *path);
bool	is_parameter_file(char *cmd_parameter);
bool	is_parameter_dir(char *cmd_parameter);
void	cp_argv(char **argv, t_pipex *pipex);
int		get_element_count(char **array);
int		get_cmd_count(char **argv, char **h_envp);
int		get_cmd_absolute_path_count(t_pipex *pipex);
int		get_pipe_count(char **argv);
int		get_builtin_cmd_count(t_pipex *pipex);
void	get_order(t_env *node);
int		get_arg_i(int pipe_count, char **argv);
char	*getenv_from_h_envp(char **h_envp, char *varname);
char	*getenv_from_t_env(t_env *env, char *varname);
int		is_cmd(char **argv, int arg_i, char **h_envp);
bool	is_specified_redirect(char *str);
bool	is_io_file(char **argv, int arg_i);
bool	get_cmd_absolute_path(char **h_envp, t_pipex *pipex);
bool	add_absolute_path_to_cmd_name(char **h_envp,
			char ***cmd_absolute_path);
char	**add_slash_eos(char **path);
int		get_cmd_arg_fd(t_pipex *pipex, int cmd_i);
bool	proc_here_doc(char *delimiter, t_pipex *pipex, char **h_envp);
bool	rm_here_doc(void);
bool	is_cmd_relative_path(char ***cmd_absolute_path, int cmd_i);
bool	is_cmd_alreadly_absollute_path(char ***cmd_absolute_path, int cmd_i);
bool	wait_children(int cmd_i);
bool	reset_pipex(t_pipex *pipex, int cmd_i);
int		pipex(char **argv, char **h_envp, t_env **env);
bool	get_pipex(char **argv, char **h_envp, t_pipex *pipex);
bool	do_pipex(char **h_envp, t_env **env, t_pipex *pipex);
bool	end_pipex(t_pipex *pipex);

// is_specified_file
bool	is_specified_infile(char *str);
bool	is_specified_here_doc(char *str);
bool	is_specified_outfile_overwriting(char *str);
bool	is_specified_outfile_apend(char *str);
bool	is_specified_operators(char *str);

// get_fd
bool	get_fd(t_pipex *pipex, char **argv, char **h_envp);
bool	get_infile_fd(t_pipex *pipex, char **argv, char **h_envp);
bool	get_outfile_fd(t_pipex *pipex, char **argv);

// is_file_ok
bool	is_file_exist(char *file);
bool	is_file_readable(char *file);
bool	is_file_writable(char *file);
bool	is_file_exectable(char *file);

// is_specified_control_operators
bool	is_specified_semicolon(char *str);
bool	is_specified_pipe(char *str);
bool	is_specified_pipe_pipe(char *str);
bool	is_specified_ampersant(char *str);
bool	is_specified_apersant_ampersant(char *str);

// set_fd
bool	set_input_fd(t_pipex *pipex, int cmd_i);
bool	set_output_fd(t_pipex *pipex, int cmd_i);
bool	reset_fd(int *stdin_fileno, int *stdout_fileno);

// array_node
t_env	*array_to_node(char **envp);
char	**node_to_array(t_env *env);

// node
t_env	*ft_nodenew(char *content);
void	ft_nodeadd_front(t_env **node, t_env *new);
void	ft_nodeadd_back(t_env **node, t_env *new);
void	ft_nodedelone(t_env **node);
void	ft_nodeclear(t_env **node);
void	ft_nodenext(t_env **node);
void	ft_nodeprev(t_env **node);
void	ft_nodefirst(t_env **node);
t_env	*ft_nodelast(t_env *node);
int		ft_nodesize(t_env *node);

void	put_node_for_debug(t_env *node);
void	put_array_for_debug(char **str);

// loop_pipex
int		loop_pipex(char **argv, t_env **env);
void	get_loop_pipex(char **argv, char ****splitted_argv, char ***splitter);
int		do_loop_pipex(char ***splitted_argv, char **splitter, t_env **env);
void	end_loop_pipex(char ***splitted_argv, char **splitter);
char	***get_splitted_argv(char **argv);
char	**get_splitter(char **argv);
int		get_splitter_count(char **argv);
int		is_specified_splitter(char *str);
bool	is_splitter_exist(char **argv);

// put_error
void	put_error(char *err_msg);
void	put_error_w_cmd(char *cmd, char *error_msg);
void	put_error_w_file(char *file, char *error_msg);
void	put_error_w_cmd_filename(char *cmdname, char *filename,
			char *error_msg);
int		put_file_error(char *cmd, char *file);

#endif
