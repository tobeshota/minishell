/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 01:22:30 by toshota           #+#    #+#             */
/*   Updated: 2023/12/09 20:33:49 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_arg_start_pos(int pipe_count, char **argv)
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

bool	get_infile_fd(t_pipex *pipex, char **argv, int exec_flag)
{
	int	arg_i;

	arg_i = 0;
	pipex->infile_fd = STDIN_FILENO;
	while (argv[arg_i] && !is_specified_pipe(argv[arg_i]))
	{
		if (is_specified_infile(argv[arg_i]) && argv[arg_i + 1])
		{
			pipex->infile_fd = open_file(argv[arg_i + 1], INFILE);
			if (check_open(pipex->infile_fd, argv[arg_i + 1]) == false)
				return (false);
		}
		else if (is_specified_here_doc(argv[arg_i]) && \
		argv[arg_i + 1] && exec_flag == true)
			if (proc_here_doc(argv[arg_i + 1], pipex) == false)
				return (false);
		arg_i++;
	}
	return (true);
}

bool	get_outfile_fd(t_pipex *pipex, char **argv)
{
	int	arg_i;

	arg_i = 0;
	pipex->outfile_fd = STDOUT_FILENO;
	while (argv[arg_i] && !is_specified_pipe(argv[arg_i]))
	{
		if (is_specified_outfile_overwriting(argv[arg_i]) && argv[arg_i + 1])
			pipex->outfile_fd = \
			open_file(argv[arg_i + 1], OUTFILE_OVER_WRITING);
		else if (is_specified_outfile_apend(argv[arg_i]) && argv[arg_i + 1])
			pipex->outfile_fd = \
			open_file(argv[arg_i + 1], OUTFILE_APEND);
		if (check_open(pipex->outfile_fd, argv[arg_i + 1]) == false)
			return (false);
		arg_i++;
	}
	return (true);
}
