/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 22:46:35 by toshota           #+#    #+#             */
/*   Updated: 2023/12/19 23:40:24 by toshota          ###   ########.fr       */
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

static bool	do_execve(char **h_envp, t_pipex *pipex, int cmd_i)
{
	char	**cmd;
	char	*cmd_abspath_w_param_wo_encloser;
	char	*cmd_abspath_wo_encloser;
	int		ret;

	cmd_abspath_w_param_wo_encloser = \
	omit_str(pipex->cmd_absolute_path_with_parameter[cmd_i], "\'\"");
	cmd = check_malloc(ft_split(cmd_abspath_w_param_wo_encloser, ' '));
	cmd_abspath_wo_encloser = omit_str(pipex->cmd_absolute_path[cmd_i], "\'\"");
	ret = check_execve(execve \
	(cmd_abspath_wo_encloser, cmd, h_envp), cmd_abspath_wo_encloser, pipex);
	free(cmd_abspath_w_param_wo_encloser);
	free(cmd_abspath_wo_encloser);
	if (ret == false)
		exit(126);
	else
		return (true);
}

static bool	do_exec_builtin(t_env **env, t_pipex *pipex, int cmd_i)
{
	return (check_exec_builtin(exec_builtin \
	(env, pipex, cmd_i), pipex->cmd_absolute_path[cmd_i], pipex));
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

bool	do_pipex(char **h_envp, t_env **env, t_pipex *pipex, t_tools *tools)
{
	int		cmd_i;
	pid_t	child_pid;

	cmd_i = 0;
	while (pipex->cmd_absolute_path[cmd_i])
	{
		if (cmd_i < get_pipe_count(pipex->argv) && !get_pipe(pipex, cmd_i))
			return (false);
		if (is_cmd_builtin(pipex->cmd_absolute_path[cmd_i]))
		{
			if (exec(h_envp, env, pipex, cmd_i) == false)
				return (false);
		}
		else if (get_child(&child_pid) == false \
			|| (child_pid == 0 && exec(h_envp, env, pipex, cmd_i) == false))
			return (false);
		if (reset_pipex(pipex, cmd_i) == false || ++cmd_i < 0 || \
		!get_fd(pipex, pipex->argv + \
		get_arg_i(cmd_i, pipex->argv), h_envp, tools))
			return (false);
	}
	if (close_fd(pipex) == false)
		return (false);
	return (wait_children(cmd_i - get_builtg_in_cmd_count(pipex), pipex));
}
