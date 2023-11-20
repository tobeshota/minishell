/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:14:49 by toshota           #+#    #+#             */
/*   Updated: 2023/11/20 10:50:56 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	set_input_fd(t_pipex_data *pipex_data, int cmd_i, char **argv)
{
	if (get_infile_fd(pipex_data, cmd_i, argv) == false
		|| check_open(get_cmd_arg_fd(pipex_data, cmd_i)) == false)
		return (false);
	if (get_cmd_arg_fd(pipex_data, cmd_i) != NOT_SPECIFIED)
	{
		if (check_dup(dup2(get_cmd_arg_fd(pipex_data, cmd_i),
					STDIN_FILENO)) == false)
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
	else
	{
		if (check_dup(dup2(pipex_data->infile_fd, STDIN_FILENO)) == false)
			return (false);
		return (check_close(close(pipex_data->infile_fd)));
	}
}

static int	set_output_fd(t_pipex_data *pipex_data, int cmd_i, char **argv)
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

static int	exec_child(char ***envp, t_pipex_data *pipex_data, int cmd_i,
		char **argv)
{
	char	**cmd;

	cmd = check_malloc \
	(ft_split(pipex_data->cmd_absolute_path_with_parameter[cmd_i], ' '));
	if (set_input_fd(pipex_data, cmd_i, argv) == false)
		return (false);
	if (set_output_fd(pipex_data, cmd_i, argv) == false)
		return (false);
	if (check_execve(execve(pipex_data->cmd_absolute_path[cmd_i], cmd,
				*envp)) == false)
		return (false);
	return (true);
}

static int	get_child(pid_t *child_pid)
{
	*child_pid = fork();
	if (check_fork(*child_pid) == false)
		return (false);
	return (true);
}

int	do_pipe(char ***envp, t_pipex_data *pipex_data, char **argv)
{
	int		cmd_i;
	pid_t	child_pid;

	cmd_i = 0;
	while (pipex_data->cmd_absolute_path[cmd_i])
	{
		if (get_pipe(pipex_data, cmd_i) == false)
			return (false);
		if (get_child(&child_pid) == false)
			return (false);
		if (child_pid == 0 && exec_child(envp, pipex_data, cmd_i,
				argv) == false)
			return (false);
		if (cmd_i > 0 && close_pipe(pipex_data->pipe_fd[cmd_i - 1]) == false)
			return (false);
		cmd_i++;
	}
	if (wait_children(cmd_i) == false)
		return (false);
	return (true);
}
