/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 09:29:26 by toshota           #+#    #+#             */
/*   Updated: 2023/12/21 10:58:32 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "builtin.h"
# include "define.h"
# include "libft.h"
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

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
int		close_file(int fd, int default_fd);
bool	close_pipe(int *pipe_fd);
int		free_tab(char *ptr);
void	all_free_tab(char **ptr);
void	all_free_int(int **ptr);
size_t	strlen_until_c(char *str, char c);
int		ft_strrncmp(const char *s1, const char *s2, size_t n);
char	*double_to_sigle(char **array, char splitter);
void	*check_malloc(void *ptr);
bool	check_getenv(char *ptr);
bool	check_opendir(DIR *dir, char *path);
bool	check_closedir(int ret);
bool	check_open(int fd, char *file, t_pipex *pipex);
bool	check_close(int ret);
bool	check_pipe(int ret);
bool	check_fork(pid_t child_pid);
bool	check_dup(int ret);
bool	check_execve(int ret, char *cmd, t_pipex *pipex);
bool	check_exec_builtin(int ret, char *cmd, t_pipex *pipex);
bool	check_is_dir(char *filename, int ret, t_pipex *pipex);
bool	check_cmd_exist(char *filename, int ret, t_pipex *pipex);
bool	check_is_dot(int ret, t_pipex *pipex);
bool	check_wait(int ret);
bool	check_unlink(int ret);
bool	is_path_found(char *path);
bool	is_parameter_dir(char *cmd_parameter);
void	cp_argv(char **argv, t_pipex *pipex);
int		get_element_count(char **array);
int		get_cmd_count(t_pipex *pipex, char **h_envp);
int		get_cmd_count_wo_error_msg(t_pipex *pipex, char **h_envp);
int		get_cmd_absolute_path_count(t_pipex *pipex);
int		count_builtin(t_pipex *pipex);
void	get_order(t_env *node);
int		get_arg_i(int pipe_count, char **argv);
void	get_argv_wo_param(char **argv, int arg_i, char **cunnret_argv,
			char **prev_argv);
char	*getenv_from_h_envp(char **h_envp, char *varname);
char	*getenv_from_t_env(t_env *env, char *varname);
int		is_cmd(char *cunnret_argv, char *prev_argv, char **h_envp);
bool	is_specified_redirect(char *str);
bool	is_io_file(char *argv, char *prev_argv);
bool	get_cmd_absolute_path(char **h_envp, t_pipex *pipex);
bool	add_absolute_path_to_cmd_name(char **h_envp,
			char ***cmd_absolute_path);
char	**add_slash_eos(char **path);
int		get_cmd_arg_fd(t_pipex *pipex, int cmd_i);
bool	proc_here_doc(char *delimiter, t_pipex *pipex, char **h_envp,
			t_tools *tools);
bool	rm_here_doc(void);
bool	is_cmd_relative_path(char ***cmd_absolute_path, int cmd_i);
bool	is_cmd_alreadly_absollute_path(char ***cmd_absolute_path, int cmd_i);
bool	wait_child(int cmd_i, t_pipex *pipex);
bool	reset_pipex(char **h_envp, t_pipex *pipex, t_tools *tools, int cmd_i);
int		pipex(char **argv, char **h_envp, t_env **env, t_tools *tools);
bool	get_pipex(char **argv, char **h_envp, t_pipex *pipex, t_tools *tools);
bool	do_pipex(char **h_envp, t_env **env, t_pipex *pipex, t_tools *tools);
bool	end_pipex(t_pipex *pipex);

// is_specified_file
bool	is_specified_infile(char *str);
bool	is_specified_here_doc(char *str);
bool	is_specified_outfile_overwriting(char *str);
bool	is_specified_outfile_apend(char *str);
bool	is_specified_operators(char *str);

// get_fd
bool	get_fd(t_pipex *pipex, char **argv, char **h_envp, t_tools *tools);
bool	get_infile_fd(t_pipex *pipex, char **argv, char **h_envp,
			t_tools *tools);
bool	get_outfile_fd(t_pipex *pipex, char **argv);
bool	close_fd(t_pipex *pipex);

// is_file_ok
bool	is_file_exist(char *file);
bool	is_file_readable(char *file);
bool	is_file_writable(char *file);
bool	is_file_exectable(char *file);
bool	is_file_exectable_wo_additional_path(char *file);

// is_specified_control_operators
bool	is_specified_semicolon(char *str);
bool	is_specified_pipe(char *str);
bool	is_specified_pipe_pipe(char *str);
bool	is_specified_ampersant(char *str);
bool	is_specified_apersant_ampersant(char *str);

// omit
char	*omit_c(char *str, char c);
char	*omit_str(char *str, char *omit);
char	**omit_array(char **array, char *omit);

// set_fd
bool	set_input_fd(t_pipex *pipex, int cmd_i);
bool	set_output_fd(t_pipex *pipex, int cmd_i);
bool	reset_fd(int *stdin_fileno, int *stdout_fileno);

// get_pipex
int		count_pipe(char **argv);
bool	get_pipe(t_pipex *pipex, int cmd_i);
void	malloc_multiple_pipe(t_pipex *pipex);

// get_child
bool	get_child(pid_t *child_pid);
int		get_child_exit_status(int status);

// array_node
t_env	*array_to_node(char **envp);
char	**node_to_array(t_env *env);

// node_utils
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
void	ft_nodesort(t_env **node);
void	ft_nodeswap(t_env *n1, t_env *n2);
bool	is_node_first(t_env *node);
bool	is_node_last(t_env *node);
bool	is_node_only_one(t_env *node);
void	unset_first_node(t_env **unseted_env, t_env **env);
void	unset_last_node(t_env **unseted_env);
void	unset_middle_node(t_env *unseted_env);

// loop_pipex
int		loop_pipex(t_tools *tools, t_env **env);
void	get_loop_pipex(char **argv, char ****splitted_argv, char ***splitter);
int		do_loop_pipex(char ***splitted_argv, char **splitter, t_env **env,
			t_tools *tools);
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
void	put_error_w_cmd_filename(char *cmd, char *file, char *error_msg,
			t_pipex *pipex);
int		put_file_error(char *cmd, char *file, t_pipex *pipex);

#endif
