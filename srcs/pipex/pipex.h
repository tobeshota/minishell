/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 09:29:26 by toshota           #+#    #+#             */
/*   Updated: 2023/11/18 00:26:42 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/inc/libft.h"
# include <sys/types.h>

# define TRUE 1
# define FALSE 0
# define HERE_DOC_FILE_PATH "/tmp/here_doc"
# define INFILE 0
# define INFILE_HERE_DOC 1
# define OUTFILE_OVER_WRITING 2
# define OUTFILE_APEND 3
# define NOT_SPECIFIED 0

/* このディレクトリをminishellに移行するときにやること
・構造体t_pipex_dataの定義を消す　∵define.hに記述済みであるため
・ディレクトリ名をpipex_for_minishell/からpipex/に変える
・このディレクトリ内にある　#include "../pipex.h" を #include "pipex.h"に置換する
*/
typedef struct s_pipex_data
{
	int		infile_fd;
	int		outfile_fd;
	char	**cmd_absolute_path;
	char	**cmd_absolute_path_with_parameter;
	int		**pipe_fd;
}			t_pipex_data;

int			open_file(char *file, int file_type);
void		close_pipe(int *pipe_fd);
void		add_slash_eos(char ***path);
void		all_free_tab(char **ptr);
void		put_error(char *err_msg);
char		*ft_strrnchr(const char *s, int c, int n);
size_t		strlen_until_c(char *str, char c);
void		check_malloc(void *ptr);
void		check_open(int ret);
void		check_close(int ret);
void		check_pipe(int ret);
void		check_fork(pid_t child_pid);
void		check_dup(int ret);
void		check_execve(int ret);
void		check_wait(int ret);
void		check_unlink(int ret);
void		check_arg(char **argv);
void		check_is_path_found(char *path);
int			get_cmd_count(char **argv);
int			is_cmd(char **argv, int arg_i);
int			is_limitter(char **argv, int arg_i);
int			is_fd_default(int fd, int default_fd);
void		get_cmd_absolute_path(char **argv, char **envp,
				t_pipex_data *pipex_data);
void		add_absolute_path_to_cmd_name(char ***cmd_absolute_path,
				char **env_path, char **envp);
void		get_env_path(char ***env_path, char **envp);
void		get_pwd(char ***pwd_path, char **envp);
int			get_down_count_from_pwd(char *relative_path);
char		*get_pwd_for_relative_path(char ***pwd_path,
				int down_count_from_pwd);
void		get_pipe(t_pipex_data *pipex_data, int cmd_i);
void		proc_here_doc(char *limitter, t_pipex_data *pipex_data);
int			is_cmd_relative_path(char ***cmd_absolute_path, int cmd_i);
int			is_cmd_alreadly_absollute_path(char ***cmd_absolute_path,
				int cmd_i);
void		do_pipe(char **envp, t_pipex_data *pipex_data, char **argv);
int			pipex(int argc, char **argv, char **envp);
void		get_pipex_data(int argc, char **argv, char **envp,
				t_pipex_data *pipex_data);
void		end_pipex(t_pipex_data *pipex_data);

// is_specified_file
int			is_specified_infile(char *str);
int			is_specified_here_doc(char *str);
int			is_specified_outfile_overwriting(char *str);
int			is_specified_outfile_apend(char *str);
int			is_specified_operators(char *str);

void	get_infile_fd(t_pipex_data *pipex_data, int cmd_i, char **argv);
void	get_outfile_fd(t_pipex_data *pipex_data, int cmd_i, char **argv);

// is_file_ok
int is_file_exist(char *file);
int is_file_readable(char *file);
int is_file_writable(char *file);
int is_file_exectable(char *file);

// is_specified_control_operators
int			is_specified_semicolon(char *str);
int			is_specified_pipe(char *str);
int			is_specified_pipe_pipe(char *str);
int			is_specified_ampersant(char *str);
int			is_specified_apersant_ampersant(char *str);

#endif
