/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 22:46:35 by toshota           #+#    #+#             */
/*   Updated: 2023/12/02 00:19:57 by toshota          ###   ########.fr       */
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

/* STDIN_FILENO,STDOUT＿FILENOそれぞれをdup();で複製しておき，reset_fd();でdup2();にてもとに戻す！ */
static bool	exec(char **argv, t_env **env, t_pipex *pipex, int cmd_i)
{
	char		**cmd;
	extern char	**environ;
	int			stdin_fileno;
	int			stdout_fileno;

	dup_std_fileno(&stdin_fileno, &stdout_fileno);
	if (set_input_fd(pipex, cmd_i, argv) == false)
		return (reset_fd(pipex, &stdin_fileno, &stdout_fileno), false);
	if (set_output_fd(pipex, cmd_i, argv) == false)
		return (reset_fd(pipex, &stdin_fileno, &stdout_fileno), false);
	if (is_cmd_builtin(pipex->cmd_absolute_path[cmd_i]))
	{
		if (exec_builtin(env, pipex, cmd_i) == false)
			return (reset_fd(pipex, &stdin_fileno, &stdout_fileno), false);
		return (reset_fd(pipex, &stdin_fileno, &stdout_fileno));
	}
	else
	{
		cmd = check_malloc \
		(ft_split(pipex->cmd_absolute_path_with_parameter[cmd_i], ' '));
		return (check_exec \
		(execve(pipex->cmd_absolute_path[cmd_i], cmd, environ)));
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

/* builtinコマンドをパイプと組み合わせて使用できるようにする！ */
bool	do_pipex(char **argv, t_env **env, t_pipex *pipex)
{
	int		cmd_i;
	pid_t	child_pid;

	cmd_i = -1;
	while (pipex->cmd_absolute_path[++cmd_i])
	{
		if (cmd_i < get_pipe_count(argv) && get_pipe(pipex, cmd_i) == false)
			return (false);
		if (is_cmd_builtin(pipex->cmd_absolute_path[cmd_i]))
		{
			if (exec(argv, env, pipex, cmd_i) == false)
				return (false);
		}
		else
		{
			if (get_child(&child_pid) == false)
				return (false);
			if (child_pid == 0 && exec(argv, env, pipex, cmd_i) == false)
				return (false);
		}
		if (cmd_i > 0 && close_pipe(pipex->pipe_fd[cmd_i - 1]) == false)
			return (false);
	}
	return (wait_children(cmd_i - get_builtin_cmd_count(pipex)));
}
