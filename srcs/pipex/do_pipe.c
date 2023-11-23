/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:14:49 by toshota           #+#    #+#             */
/*   Updated: 2023/11/23 17:08:17 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static bool	set_input_fd(t_pipex_data *pipex_data, int cmd_i, char **argv)
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

static bool	set_output_fd(t_pipex_data *pipex_data, int cmd_i, char **argv)
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

static bool	exec(char ***envp, t_pipex_data *pipex_data, int cmd_i,
		char **argv)
{
	char	**cmd;

	if (set_input_fd(pipex_data, cmd_i, argv) == false)
		return (false);
	if (set_output_fd(pipex_data, cmd_i, argv) == false)
		return (false);
	if (is_cmd_builtin(pipex_data->cmd_absolute_path[cmd_i]))
	{
		return (check_exec(exec_builtin(envp, pipex_data, cmd_i)));
	}
	else
	{
		cmd = check_malloc \
		(ft_split(pipex_data->cmd_absolute_path_with_parameter[cmd_i], ' '));
		return (check_exec(execve(pipex_data->cmd_absolute_path[cmd_i], cmd, *envp)));
	}
}

static bool	get_child(pid_t *child_pid)
{
	*child_pid = fork();
	if (check_fork(*child_pid) == false)
		return (false);
	return (true);
}

// builitin_cmdの場合，子プロセスでは実行しない．
bool	do_pipe(char ***envp, t_pipex_data *pipex_data, char **argv)
{
	int		cmd_i;
	pid_t	child_pid;

	cmd_i = -1;
	while (pipex_data->cmd_absolute_path[++cmd_i])
	{
		if (cmd_i < get_pipe_count(argv) && get_pipe(pipex_data, cmd_i) == false)
			return (false);
		if (is_cmd_builtin(pipex_data->cmd_absolute_path[cmd_i]))
		{
			if (exec(envp, pipex_data, cmd_i, argv) == false)
				return (false);
		}
		else
		{
			if (get_child(&child_pid) == false)
				return (false);
			if (child_pid == 0 && exec(envp, pipex_data, cmd_i, argv) == false)
				return (false);
		}
		if (cmd_i > 0 && close_pipe(pipex_data->pipe_fd[cmd_i - 1]) == false)
			return (false);
	}
	return (wait_children(cmd_i - get_builtin_cmd_count(pipex_data)));
}
