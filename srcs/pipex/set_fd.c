/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 13:19:51 by toshota           #+#    #+#             */
/*   Updated: 2023/11/24 13:40:51 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool	set_input_fd(t_pipex_data *pipex_data, int cmd_i, char **argv)
{
	if (get_infile_fd(pipex_data, cmd_i, argv) == false || check_open(get_cmd_arg_fd(pipex_data, cmd_i)) == false)
		return (false);
	if (get_cmd_arg_fd(pipex_data, cmd_i) != NOT_SPECIFIED)
	{
		if (check_dup(dup2(get_cmd_arg_fd(pipex_data, cmd_i), STDIN_FILENO)) == false)
			return (false);
		return (check_close(close(get_cmd_arg_fd(pipex_data, cmd_i))));
	}
	else if (is_fd_default(pipex_data->infile_fd, STDIN_FILENO) && cmd_i != 0)
	{
		if (check_dup(dup2(pipex_data->pipe_fd[cmd_i - 1][0],
				STDIN_FILENO)) == false)
			return (false);
		return (close_pipe(pipex_data->pipe_fd[cmd_i - 1]));
	}
	else if (!is_fd_default(pipex_data->infile_fd, STDIN_FILENO))
	{
		if (check_dup(dup2(pipex_data->infile_fd, STDIN_FILENO)) == false)
			return (false);
		return (check_close(close(pipex_data->infile_fd)));
	}
	return (true);
}

bool	set_output_fd(t_pipex_data *pipex_data, int cmd_i, char **argv)
{
	if (get_outfile_fd(pipex_data, cmd_i, argv) == false)
		return (false);
	if (is_fd_default(pipex_data->outfile_fd, STDOUT_FILENO)
		&& pipex_data->cmd_absolute_path[cmd_i + 1] != NULL)
	{
		if (check_dup(dup2(pipex_data->pipe_fd[cmd_i][1],
				STDOUT_FILENO)) == false)
			return (false);
		return (close_pipe(pipex_data->pipe_fd[cmd_i]));
	}
	else if (!is_fd_default(pipex_data->outfile_fd, STDOUT_FILENO))
	{
		if (check_dup(dup2(pipex_data->outfile_fd, STDOUT_FILENO)) == false)
			return (false);
		return (check_close(close(pipex_data->outfile_fd)));
	}
	return (true);
}

bool	reset_fd(t_pipex_data *pipex_data)
{
	if (is_fd_default(pipex_data->infile_fd, STDIN_FILENO) == false)
	{
		puts("infile!\n");
		pipex_data->infile_fd = STDIN_FILENO;
		if (check_dup(dup2(pipex_data->infile_fd, STDIN_FILENO)) == false)
			return (false);
		check_close(close(pipex_data->infile_fd));
	}
	if (is_fd_default(pipex_data->outfile_fd, STDOUT_FILENO) == false)
	{
		puts("outfile!\n");

		pipex_data->outfile_fd = STDOUT_FILENO;
		if (check_dup(dup2(pipex_data->outfile_fd, STDOUT_FILENO)) == false)
			return (false);
		check_close(close(pipex_data->outfile_fd));
	}
	return true;
}
