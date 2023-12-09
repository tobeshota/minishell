/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 22:46:35 by toshota           #+#    #+#             */
/*   Updated: 2023/12/09 19:27:17 by toshota          ###   ########.fr       */
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

static bool	exec(char **heap_envp, t_env **env, t_pipex *pipex, int cmd_i)
{
	char		**cmd;
	int			stdin_fileno;
	int			stdout_fileno;

	dup_std_fileno(&stdin_fileno, &stdout_fileno);
	if (set_input_fd(pipex, cmd_i) == false)
		return (reset_fd(&stdin_fileno, &stdout_fileno), false);
	if (set_output_fd(pipex, cmd_i) == false)
		return (reset_fd(&stdin_fileno, &stdout_fileno), false);
	if (is_cmd_builtin(pipex->cmd_absolute_path[cmd_i]))
	{
		if (check_exec_builtin \
		(exec_builtin(env, pipex, cmd_i), \
		pipex->cmd_absolute_path[cmd_i]) == false)
			return (reset_fd(&stdin_fileno, &stdout_fileno), false);
		return (reset_fd(&stdin_fileno, &stdout_fileno));
	}
	else
	{
		cmd = check_malloc \
		(ft_split(pipex->cmd_absolute_path_with_parameter[cmd_i], ' '));
		return (check_execve \
		(execve(pipex->cmd_absolute_path[cmd_i], cmd, heap_envp), \
		pipex->cmd_absolute_path[cmd_i]));
	}
}

static bool	get_pipe(t_pipex *pipex, int cmd_i)
{
	return (check_pipe(pipe(pipex->pipe_fd[cmd_i])));
}

static bool	get_child(pid_t *child_pid)
{
	*child_pid = fork();
	if (check_fork(*child_pid) == false)
		return (false);
	return (true);
}

bool	do_pipex(char **argv, char **heap_envp, t_env **env, t_pipex *pipex)
{
	int		cmd_i;
	pid_t	child_pid;

	cmd_i = -1;
	while (pipex->cmd_absolute_path[++cmd_i])
	{
		get_infile_fd(pipex, cmd_i, argv, true);
		get_outfile_fd(pipex, cmd_i, argv);
		if (cmd_i < get_pipe_count(argv) && get_pipe(pipex, cmd_i) == false)
			return (false);
		if (is_cmd_builtin(pipex->cmd_absolute_path[cmd_i]))
		{
			if (exec(heap_envp, env, pipex, cmd_i) == false)
				return (false);
		}
		else
		{
			if (get_child(&child_pid) == false \
			|| (child_pid == 0 && exec(heap_envp, env, pipex, cmd_i) == false))
				return (false);
		}
		if (cmd_i > 0 && close_pipe(pipex->pipe_fd[cmd_i - 1]) == false)
			return (false);
	}
	return (wait_children(cmd_i - get_builtin_cmd_count(pipex)));
}
