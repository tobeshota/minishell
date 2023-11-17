/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 01:22:30 by toshota           #+#    #+#             */
/*   Updated: 2023/11/18 01:28:26 by toshota          ###   ########.fr       */
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

void	get_infile_fd(t_pipex_data *pipex_data, int cmd_i, char **argv)
{
	int	arg_i;

	arg_i = get_start_pos(cmd_i, argv);
	pipex_data->infile_fd = STDIN_FILENO;
	while (argv[arg_i] && !is_specified_pipe(argv[arg_i]))
	{
		if (is_specified_infile(argv[arg_i]))
			pipex_data->infile_fd = open_file(argv[arg_i + 1], INFILE);
		else if (is_specified_here_doc(argv[arg_i]))
			proc_here_doc(argv[arg_i + 1], pipex_data);
		arg_i++;
	}
}

void	get_outfile_fd(t_pipex_data *pipex_data, int cmd_i, char **argv)
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
		arg_i++;
	}
}

static int	is_parameter_arg(char *cmd_parameter)
{
	return (cmd_parameter[0] != '\0' && cmd_parameter[0] != '-'
		&& is_file_exist(cmd_parameter));
}

int	get_cmd_arg_fd(t_pipex_data *pipex_data, int cmd_i)
{
	int		cmd_arg_fd;
	char	*cmd_parameter;

	cmd_parameter = ft_substr \
	(pipex_data->cmd_absolute_path_with_parameter[cmd_i],
			strlen_until_c(pipex_data->cmd_absolute_path_with_parameter[cmd_i],
				' ') + 1,
			ft_strlen(pipex_data->cmd_absolute_path_with_parameter[cmd_i]));
	check_malloc(cmd_parameter);
	if (is_parameter_arg(cmd_parameter))
		cmd_arg_fd = open_file(cmd_parameter, INFILE);
	else
		cmd_arg_fd = NOT_SPECIFIED;
	free(cmd_parameter);
	return (cmd_arg_fd);
}
