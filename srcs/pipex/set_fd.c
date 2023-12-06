/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 13:19:51 by toshota           #+#    #+#             */
/*   Updated: 2023/12/06 12:30:31 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static bool	is_fd_default(int fd, int default_fd)
{
	return (fd == default_fd);
}

bool	set_input_fd(t_pipex *pipex, int cmd_i, char **argv)
{
	if (get_infile_fd(pipex, cmd_i, argv, true) == false
		|| check_open(get_cmd_arg_fd(pipex, cmd_i), NULL) == false)
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
		if (is_cmd_builtin(pipex->cmd_absolute_path[cmd_i]) == false)
			return (close_pipe(pipex->pipe_fd[cmd_i - 1]));
	}
	else if (!is_fd_default(pipex->infile_fd, STDIN_FILENO))
	{
		if (check_dup(dup2(pipex->infile_fd, STDIN_FILENO)) == false)
			return (false);
	}
	return (true);
}

bool	set_output_fd(t_pipex *pipex, int cmd_i, char **argv)
{
	if (get_outfile_fd(pipex, cmd_i, argv) == false)
		return (false);
	if (is_fd_default(pipex->outfile_fd, STDOUT_FILENO)
		&& pipex->cmd_absolute_path[cmd_i + 1] != NULL)
	{
		if (check_dup(dup2(pipex->pipe_fd[cmd_i][1], STDOUT_FILENO)) == false)
			return (false);
		pipex->outfile_fd = pipex->pipe_fd[cmd_i][1];
	}
	else if (!is_fd_default(pipex->outfile_fd, STDOUT_FILENO))
	{
		if (check_dup(dup2(pipex->outfile_fd, STDOUT_FILENO)) == false)
			return (false);
	}
	return (true);
}

bool	reset_fd(t_pipex *pipex, int *stdin_fileno, int *stdout_fileno)
{
	if (check_dup(dup2(*stdin_fileno, STDIN_FILENO)) == false)
		return (false);
	if (check_dup(dup2(*stdout_fileno, STDOUT_FILENO)) == false)
		return (false);
	return (true);
}
