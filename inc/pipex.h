/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 09:29:26 by toshota           #+#    #+#             */
/*   Updated: 2023/11/22 14:29:56 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "builtin.h"
# include "define.h"
# include "libft.h"
# include <sys/types.h>

# define HERE_DOC_FILE_PATH "/tmp/here_doc"
# define INFILE 0
# define INFILE_HERE_DOC 1
# define OUTFILE_OVER_WRITING 2
# define OUTFILE_APEND 3
# define NOT_SPECIFIED 0

int		open_file(char *file, int file_type);
bool	close_pipe(int *pipe_fd);
void	add_slash_eos(char ***path);
void	all_free_tab(char **ptr);
void	put_error(char *err_msg);
char	*ft_strrnchr(const char *s, int c, int n);
size_t	strlen_until_c(char *str, char c);
void	*check_malloc(void *ptr);
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
int		get_builtin_cmd_count(t_pipex_data *pipex_data);
bool	convert_relative_path_to_absolute_path(char ***cmd_absolute_path, int cmd_i, char **envp);
bool	is_cmd(char **argv, int arg_i);
bool	is_limitter(char **argv, int arg_i);
bool	is_fd_default(int fd, int default_fd);
bool	get_cmd_absolute_path(char **argv, char **envp,
			t_pipex_data *pipex_data);
bool	add_absolute_path_to_cmd_name(char ***cmd_absolute_path,
			char **env_path, char **envp);
bool	get_env_path(char ***env_path, char **envp);
bool	get_pwd(char ***pwd_path, char **envp);
int		get_down_count_from_pwd(char *relative_path);
int		get_cmd_arg_fd(t_pipex_data *pipex_data, int cmd_i);
void	get_cmd_parameter(char **argv, char ***cmd_absolute_path,
		char ***cmd_parameter);
char	*get_pwd_for_relative_path(char ***pwd_path, int down_count_from_pwd);
bool	get_pipe(t_pipex_data *pipex_data, int cmd_i);
bool	proc_here_doc(char *limitter, t_pipex_data *pipex_data);
bool	is_cmd_relative_path(char ***cmd_absolute_path, int cmd_i);
bool	is_cmd_alreadly_absollute_path(char ***cmd_absolute_path, int cmd_i);
bool	do_pipe(char ***envp, t_pipex_data *pipex_data, char **argv);
bool	wait_children(int cmd_i);
int		pipex(int argc, char **argv, char ***envp);
bool	get_pipex_data(int argc, char **argv, char **envp,
			t_pipex_data *pipex_data);
bool	end_pipex(t_pipex_data *pipex_data);

// is_specified_file
bool	is_specified_infile(char *str);
bool	is_specified_here_doc(char *str);
bool	is_specified_outfile_overwriting(char *str);
bool	is_specified_outfile_apend(char *str);
bool	is_specified_operators(char *str);

bool	get_infile_fd(t_pipex_data *pipex_data, int cmd_i, char **argv);
bool	get_outfile_fd(t_pipex_data *pipex_data, int cmd_i, char **argv);

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

#endif
