/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 01:22:30 by toshota           #+#    #+#             */
/*   Updated: 2023/12/20 16:39:35 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "expander.h"

int	get_arg_i(int pipe_count, char **argv)
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

bool	get_infile_fd(t_pipex *pipex, char **argv, char **h_envp,
		t_tools *tools)
{
	int	arg_i;

	arg_i = 0;
	while (argv[arg_i] && !is_specified_pipe(argv[arg_i]))
	{
		if (is_specified_infile(argv[arg_i]) && argv[arg_i + 1])
		{
			if (!check_close(close_file(pipex->infile_fd, STDIN_FILENO)))
				return (false);
			pipex->infile_fd = open_file(argv[arg_i + 1], INFILE);
			if (check_open(pipex->infile_fd, argv[arg_i + 1], pipex) == false)
				return (false);
		}
		else if (is_specified_here_doc(argv[arg_i]) && argv[arg_i + 1] \
		&& g_in_cmd != SIG_INT_COMING)
		{
			if (!check_close(close_file(pipex->infile_fd, STDIN_FILENO)))
				return (false);
			if (proc_here_doc(argv[arg_i + 1], pipex, h_envp, tools) == false)
				return (false);
		}
		arg_i++;
	}
	return (true);
}

bool	get_outfile_fd(t_pipex *pipex, char **argv)
{
	int	arg_i;

	arg_i = 0;
	while (argv[arg_i] && !is_specified_pipe(argv[arg_i]))
	{
		if (is_specified_outfile_overwriting(argv[arg_i]) && argv[arg_i + 1])
		{
			if (!check_close(close_file(pipex->outfile_fd, STDOUT_FILENO)))
				return (false);
			pipex->outfile_fd = \
				open_file(argv[arg_i + 1], OUTFILE_OVER_WRITING);
		}
		else if (is_specified_outfile_apend(argv[arg_i]) && argv[arg_i + 1])
		{
			if (!check_close(close_file(pipex->outfile_fd, STDOUT_FILENO)))
				return (false);
			pipex->outfile_fd = \
				open_file(argv[arg_i + 1], OUTFILE_APEND);
		}
		if (check_open(pipex->outfile_fd, argv[arg_i + 1], pipex) == false)
			return (false);
		arg_i++;
	}
	return (true);
}

bool	get_fd(t_pipex *pipex, char **argv, char **h_envp, t_tools *tools)
{
	if (get_outfile_fd(pipex, argv) == false)
		return (false);
	if (get_infile_fd(pipex, argv, h_envp, tools) == false)
		return (false);
	return (true);
}

bool	close_fd(t_pipex *pipex)
{
	int	infd_ret;
	int	outfd_ret;

	infd_ret = check_close(close_file(pipex->infile_fd, STDIN_FILENO));
	outfd_ret = check_close(close_file(pipex->outfile_fd, STDOUT_FILENO));
	if (infd_ret == false || outfd_ret == false)
		return (false);
	return (true);
}
