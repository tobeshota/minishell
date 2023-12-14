/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 22:46:35 by toshota           #+#    #+#             */
/*   Updated: 2023/12/14 14:12:56 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static bool	dup_std_fileno(int *stdin_fileno,
		int *stdout_fileno)
{
	*stdin_fileno = dup(STDIN_FILENO);
	if (check_dup(*stdin_fileno) == false)
		return (false);
	*stdout_fileno = dup(STDOUT_FILENO);
	if (check_dup(*stdout_fileno) == false)
		return (false);
	return (true);
}

static bool do_execve(char **h_envp, t_pipex *pipex, int cmd_i)
{
	char	**cmd;

	cmd = check_malloc(ft_split(pipex->cmd_absolute_path_with_parameter[cmd_i], ' '));
	return (check_execve(execve(pipex->cmd_absolute_path[cmd_i], cmd, h_envp), pipex->cmd_absolute_path[cmd_i]));
}

static bool do_exec_builtin(t_env **env, t_pipex *pipex, int cmd_i)
{
	return (check_exec_builtin(exec_builtin(env, pipex, cmd_i), pipex->cmd_absolute_path[cmd_i]));
}

static bool	exec(char **h_envp, t_env **env, t_pipex *pipex, int cmd_i)
{
	int		stdin_fileno;
	int		stdout_fileno;

	dup_std_fileno(&stdin_fileno, &stdout_fileno);
	if (set_input_fd(pipex, cmd_i) == false)
		return (reset_fd(&stdin_fileno, &stdout_fileno), false);
	if (set_output_fd(pipex, cmd_i) == false)
		return (reset_fd(&stdin_fileno, &stdout_fileno), false);
	if (is_cmd_builtin(pipex->cmd_absolute_path[cmd_i]))
	{
		if (do_exec_builtin(env, pipex, cmd_i) == false)
			return (reset_fd(&stdin_fileno, &stdout_fileno), false);
		return (reset_fd(&stdin_fileno, &stdout_fileno));
	}
	else
		return (do_execve(h_envp, pipex, cmd_i));
}

bool	do_pipex(char **h_envp, t_env **env, t_pipex *pipex)
{
	int		cmd_i;
	pid_t	child_pid;

	cmd_i = -1;
	while (pipex->cmd_absolute_path[++cmd_i])
	{
		if (!get_fd(pipex, pipex->argv + get_arg_i(cmd_i, pipex->argv), h_envp))
			return (false);
		if (cmd_i < get_pipe_count(pipex->argv) && !get_pipe(pipex, cmd_i))
			return (false);
		if (is_cmd_builtin(pipex->cmd_absolute_path[cmd_i]))
		{
			if (exec(h_envp, env, pipex, cmd_i) == false)
				return (false);
		}
		else
		{
			if (get_child(&child_pid) == false \
			|| (child_pid == 0 && exec(h_envp, env, pipex, cmd_i) == false))
				return (false);
		}
		if (reset_pipex(pipex, cmd_i) == false)
			return (false);
	}
	return (wait_children(cmd_i - get_builtin_cmd_count(pipex)));
}
