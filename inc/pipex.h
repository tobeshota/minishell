/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 09:29:26 by toshota           #+#    #+#             */
/*   Updated: 2023/11/27 23:17:29 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include "define.h"
# include "builtin.h"
# include <stdio.h>
# include <sys/stat.h>
# include <sys/types.h>

# define HERE_DOC_FILE_PATH "/tmp/here_doc"
# define INFILE 0
# define INFILE_HERE_DOC 1
# define OUTFILE_OVER_WRITING 2
# define OUTFILE_APEND 3
# define NOT_SPECIFIED 0

int		open_file(char *file, int file_type);
bool	close_pipe(int *pipe_fd);
void	all_free_tab(char **ptr);
void	all_free_int(int **ptr);
void	put_error(char *err_msg);
size_t	strlen_until_c(char *str, char c);
void	*check_malloc(void *ptr);
bool	check_getenv(char *ptr);
bool	check_open(int ret);
bool	check_close(int ret);
bool	check_pipe(int ret);
bool	check_fork(pid_t child_pid);
bool	check_dup(int ret);
bool	check_exec(int ret);
bool	check_wait(int ret);
bool	check_unlink(int ret);
bool	is_path_found(char *path);
int		get_cmd_count(char **argv);
int		get_pipe_count(char **argv);
int		get_builtin_cmd_count(t_pipex *pipex);
bool	is_cmd(char **argv, int arg_i);
bool	is_limitter(char **argv, int arg_i);
bool	is_fd_default(int fd, int default_fd);
bool	get_cmd_absolute_path(char **argv, t_pipex *pipex);
bool	add_absolute_path_to_cmd_name(char ***cmd_absolute_path);
int		get_cmd_arg_fd(t_pipex *pipex, int cmd_i);
void	get_cmd_parameter(char **argv, char ***cmd_absolute_path,
			char ***cmd_parameter);
bool	proc_here_doc(char *limitter, t_pipex *pipex);
bool	is_cmd_relative_path(char ***cmd_absolute_path, int cmd_i);
bool	is_cmd_alreadly_absollute_path(char ***cmd_absolute_path, int cmd_i);
bool	wait_children(int cmd_i);
int		pipex(char **argv, t_env **env);
bool	get_pipex(char **argv, t_pipex *pipex);
bool	do_pipex(char **argv, t_env **env, t_pipex *pipex);
bool	end_pipex(t_pipex *pipex);

// is_specified_file
bool	is_specified_infile(char *str);
bool	is_specified_here_doc(char *str);
bool	is_specified_outfile_overwriting(char *str);
bool	is_specified_outfile_apend(char *str);
bool	is_specified_operators(char *str);

bool	get_infile_fd(t_pipex *pipex, int cmd_i, char **argv);
bool	get_outfile_fd(t_pipex *pipex, int cmd_i, char **argv);

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
bool	set_input_fd(t_pipex *pipex, int cmd_i, char **argv);
bool	set_output_fd(t_pipex *pipex, int cmd_i, char **argv);
bool	reset_fd(t_pipex *pipex);

// array_node
t_env	*array_to_node(char **envp);
void	node_to_array(t_env *env, char ***envp);

// node
t_env	*ft_nodenew(char *content);
void	ft_nodeadd_back(t_env **node, t_env *new);
void	ft_nodedelone(t_env **node);
void	ft_nodeclear(t_env **node);
void	ft_nodenext(t_env **node);
void	ft_nodeprev(t_env **node);
void	ft_nodefirst(t_env **node);
t_env	*ft_nodelast(t_env *node);
int		ft_nodesize(t_env *node);

void put_node_for_debug(t_env *node);

#endif
