/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:14:49 by toshota           #+#    #+#             */
/*   Updated: 2023/11/24 13:29:05 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		if (check_exec(exec_builtin(envp, pipex_data, cmd_i)) == false)
			return false;
		return reset_fd(pipex_data);
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
