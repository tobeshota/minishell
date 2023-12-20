/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 13:19:51 by toshota           #+#    #+#             */
/*   Updated: 2023/12/20 12:05:45 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static bool	is_fd_default(int fd, int default_fd)
{
	return (fd == default_fd);
}

bool	set_input_fd(t_pipex *pipex, int cmd_i)
{
	if (check_open(get_cmd_arg_fd(pipex, cmd_i), NULL, pipex) == false)
		return (false);
	if (get_cmd_arg_fd(pipex, cmd_i) != NOT_SPECIFIED)
	{
		if (check_dup \
		(dup2(get_cmd_arg_fd(pipex, cmd_i), STDIN_FILENO)) == false)
			return (false);
		return (check_close(close(get_cmd_arg_fd(pipex, cmd_i))));
	}
	else if (is_fd_default(pipex->infile_fd, STDIN_FILENO) && cmd_i != 0)
	{
		if (check_dup \
		(dup2(pipex->pipe_fd[cmd_i - 1][0], STDIN_FILENO)) == false)
			return (false);
		pipex->infile_fd = pipex->pipe_fd[cmd_i - 1][0];
			return (close_pipe(pipex->pipe_fd[cmd_i - 1]));
	}
	else if (!is_fd_default(pipex->infile_fd, STDIN_FILENO))
	{
		if (check_dup(dup2(pipex->infile_fd, STDIN_FILENO)) == false)
			return (false);
		return (check_close(close(pipex->infile_fd)));
	}
	return (true);
}

bool	set_output_fd(t_pipex *pipex, int cmd_i)
{
	if (is_fd_default(pipex->outfile_fd, STDOUT_FILENO)
		&& pipex->cmd_absolute_path[cmd_i + 1] != NULL)
	{
		if (check_dup(dup2(pipex->pipe_fd[cmd_i][1], STDOUT_FILENO)) == false)
			return (false);
		pipex->outfile_fd = pipex->pipe_fd[cmd_i][1];
			return (close_pipe(pipex->pipe_fd[cmd_i]));
	}
	else if (!is_fd_default(pipex->outfile_fd, STDOUT_FILENO))
	{
		if (check_dup(dup2(pipex->outfile_fd, STDOUT_FILENO)) == false)
			return (false);
		return (check_close(close(pipex->outfile_fd)));
	}
	return (true);
}

bool	reset_fd(int *stdin_fileno, int *stdout_fileno)
{
	int	duped_infd_ret;
	int	duped_outfd_ret;
	int	closed_infd_ret;
	int	closed_outfd_ret;

	duped_infd_ret = check_dup(dup2(*stdin_fileno, STDIN_FILENO));
	duped_outfd_ret = check_dup(dup2(*stdout_fileno, STDOUT_FILENO));
	closed_infd_ret = check_close(close(*stdin_fileno));
	closed_outfd_ret = check_close(close(*stdout_fileno));
	if (duped_infd_ret == false || duped_outfd_ret == false || \
		closed_infd_ret == false || closed_outfd_ret == false)
		return (false);
	return (true);
}
