/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:14:49 by toshota           #+#    #+#             */
/*   Updated: 2023/11/18 01:25:27 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	set_input_fd(t_pipex_data *pipex_data, int cmd_i, char **argv)
{
	int	cmd_arg_fd;

	get_infile_fd(pipex_data, cmd_i, argv);
	cmd_arg_fd = get_cmd_arg_fd(pipex_data, cmd_i);
	if (cmd_arg_fd != NOT_SPECIFIED)
	{
		check_dup(dup2(cmd_arg_fd, STDIN_FILENO));
		check_close(close(cmd_arg_fd));
	}
	if (is_fd_default(pipex_data->infile_fd, STDIN_FILENO) && cmd_i != 0)
	{
		check_dup(dup2(pipex_data->pipe_fd[cmd_i - 1][0], STDIN_FILENO));
		close_pipe(pipex_data->pipe_fd[cmd_i - 1]);
	}
	else
	{
		check_dup(dup2(pipex_data->infile_fd, STDIN_FILENO));
		check_close(close(pipex_data->infile_fd));
	}
}

static void	set_output_fd(t_pipex_data *pipex_data, int cmd_i, char **argv)
{
	get_outfile_fd(pipex_data, cmd_i, argv);
	if (is_fd_default(pipex_data->outfile_fd, STDOUT_FILENO)
		&& pipex_data->cmd_absolute_path[cmd_i + 1] != NULL)
	{
		check_dup(dup2(pipex_data->pipe_fd[cmd_i][1], STDOUT_FILENO));
		close_pipe(pipex_data->pipe_fd[cmd_i]);
	}
	else if (!is_fd_default(pipex_data->outfile_fd, STDOUT_FILENO))
	{
		check_dup(dup2(pipex_data->outfile_fd, STDOUT_FILENO));
		check_close(close(pipex_data->outfile_fd));
	}
}

static void	exec_child(char **envp, t_pipex_data *pipex_data, int cmd_i,
		char **argv)
{
	char	**cmd;

	cmd = ft_split(pipex_data->cmd_absolute_path_with_parameter[cmd_i], ' ');
	check_malloc(cmd);
	set_input_fd(pipex_data, cmd_i, argv);
	set_output_fd(pipex_data, cmd_i, argv);
	check_execve(execve(pipex_data->cmd_absolute_path[cmd_i], cmd, envp));
}

void	do_pipe(char **envp, t_pipex_data *pipex_data, char **argv)
{
	int		cmd_i;
	pid_t	child_pid;

	cmd_i = 0;
	while (pipex_data->cmd_absolute_path[cmd_i])
	{
		get_pipe(pipex_data, cmd_i);
		child_pid = fork();
		check_fork(child_pid);
		if (child_pid == 0)
			exec_child(envp, pipex_data, cmd_i, argv);
		if (cmd_i > 0)
			close_pipe(pipex_data->pipe_fd[cmd_i - 1]);
		cmd_i++;
	}
	wait_children(cmd_i);
}
