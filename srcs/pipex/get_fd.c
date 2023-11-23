/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 01:22:30 by toshota           #+#    #+#             */
/*   Updated: 2023/11/23 23:36:40 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	get_start_pos(int pipe_count, char **argv)
{
	int	arg_i;

	arg_i = 0;
	while (argv[arg_i] && pipe_count)
	{
		if (is_specified_pipe(argv[arg_i]))
			pipe_count--;
		arg_i++;
	}
	return (arg_i);
}

bool	get_infile_fd(t_pipex_data *pipex_data, int cmd_i, char **argv)
{
	int	arg_i;

	arg_i = get_start_pos(cmd_i, argv);
	pipex_data->infile_fd = STDIN_FILENO;
	while (argv[arg_i] && !is_specified_pipe(argv[arg_i]))
	{
		if (is_specified_infile(argv[arg_i]))
		{
			pipex_data->infile_fd = open_file(argv[arg_i + 1], INFILE);
			if (check_open(pipex_data->infile_fd) == false)
				return (false);
		}
		else if (is_specified_here_doc(argv[arg_i]))
			if (proc_here_doc(argv[arg_i + 1], pipex_data) == false)
				return (false);
		arg_i++;
	}
	return (true);
}

bool	get_outfile_fd(t_pipex_data *pipex_data, int cmd_i, char **argv)
{
	int	arg_i;

	arg_i = get_start_pos(cmd_i, argv);
	pipex_data->outfile_fd = STDOUT_FILENO;
	while (argv[arg_i] && !is_specified_pipe(argv[arg_i]))
	{
		if (is_specified_outfile_overwriting(argv[arg_i]))
			pipex_data->outfile_fd = open_file(argv[arg_i + 1],
					OUTFILE_OVER_WRITING);
		else if (is_specified_outfile_apend(argv[arg_i]))
			pipex_data->outfile_fd = open_file(argv[arg_i + 1], OUTFILE_APEND);
		if (check_open(pipex_data->outfile_fd) == false)
			return (false);
		arg_i++;
	}
	return (true);
}

static bool is_command_parameters_included_characters_other_than_dots_and_slashes(char *cmd_parameter)
{
	int i;

	i = 0;
	while(cmd_parameter[i])
	{
		if(cmd_parameter[i] != '.' && cmd_parameter[i] != '/')
			return true;
		i++;
	}
	return false;
}

// ディレクトリでないことも確認する必要あり
static bool	is_parameter_file(char *cmd_parameter)
{
	int fd_for_checking_non_directory;
	struct stat st;

	fd_for_checking_non_directory = open_file(cmd_parameter, INFILE);
	if (fd_for_checking_non_directory == -1)
		return false;
	else if (check_close(close(fd_for_checking_non_directory)) == false)
		return false;
	else if (stat(cmd_parameter, &st) < 0)
		return perror("failt to stat"), false;
	else if (S_ISDIR(st.st_mode))
		return false;
	else if (cmd_parameter[0] == '-')
		return false;
	else if (is_file_exist(cmd_parameter) == false)
		return false;
	else if (is_command_parameters_included_characters_other_than_dots_and_slashes(cmd_parameter) == false)
		return false;
	return true;

	// return (cmd_parameter[0] != '\0' && cmd_parameter[0] != '-' && cmd_parameter[0] != '/' && is_file_exist(cmd_parameter) && is_command_parameters_included_characters_other_than_dots_and_slashes(cmd_parameter));
}

int	get_cmd_arg_fd(t_pipex_data *pipex_data, int cmd_i)
{
	int		cmd_arg_fd;
	char	*cmd_parameter;

	cmd_parameter = check_malloc \
	(ft_substr(pipex_data->cmd_absolute_path_with_parameter[cmd_i], \
	strlen_until_c \
	(pipex_data->cmd_absolute_path_with_parameter[cmd_i], ' ') + 1, \
	ft_strlen(pipex_data->cmd_absolute_path_with_parameter[cmd_i])));
	if (is_parameter_file(cmd_parameter) == true)
		cmd_arg_fd = open_file(cmd_parameter, INFILE);
	else
		cmd_arg_fd = NOT_SPECIFIED;
	free(cmd_parameter);
	return (cmd_arg_fd);
}
