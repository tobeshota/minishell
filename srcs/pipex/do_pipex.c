/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 22:46:35 by toshota           #+#    #+#             */
/*   Updated: 2023/12/29 10:22:09 by toshota          ###   ########.fr       */
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
	return (check_exec_builtin(exec_builtin(env, pipex, cmd_i), pipex));
}

bool	check_iofd(t_pipex *pipex)
{
	if (pipex->infile_fd == -1)
		return (false);
	if (pipex->outfile_fd == -1)
		return (false);
	return (true);
}

static bool	exec(char **h_envp, t_env **env, t_pipex *pipex, int cmd_i)
{
	int		stdin_fileno;
	int		stdout_fileno;

	if (check_iofd(pipex) == false)
	{
		if (is_cmd_builtin(pipex->cmd_absolute_path[cmd_i]))
			return (false);
		return (exit(1), false);
	}
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

int	get_final_cmd_exit_status(t_pipex *pipex, int cmd_i)
{
	int	final_builtin_cmd_exit_status;
	int	final_execve_cmd_exit_status;

	final_execve_cmd_exit_status = wait_child(cmd_i - count_builtin(pipex), pipex);
	final_builtin_cmd_exit_status = *pipex->error_num;
	if (is_cmd_builtin(pipex->cmd_absolute_path[cmd_i - 1]))
		*pipex->error_num = final_builtin_cmd_exit_status;
	else
		*pipex->error_num = final_execve_cmd_exit_status;
	return (*pipex->error_num == 0);
}

bool	do_pipex(char **h_envp, t_env **env, t_pipex *pipex, t_tools *tools)
{
	int		cmd_i;

	cmd_i = 0;
	/* 実行部の入出力ファイルがエラーだった場合，実行しない！ */
	while (pipex->cmd_absolute_path[cmd_i])
	{
		if (cmd_i < count_pipe(pipex->argv) && !get_pipe(pipex, cmd_i))
			return (false);
		if (is_cmd_builtin(pipex->cmd_absolute_path[cmd_i]))
		{
			if (!exec(h_envp, env, pipex, cmd_i))
				return (false);
		}
		else
		{
			if (!get_child(&pipex->pid[cmd_i]) && \
			close_pipe(pipex->pipe_fd[cmd_i]))
				return (close_pipe(pipex->pipe_fd[cmd_i - 1]), false);
			if (pipex->pid[cmd_i] == 0 && !exec(h_envp, env, pipex, cmd_i))
				return (false);
		}
		if (reset_pipex(h_envp, pipex, tools, cmd_i) == false || ++cmd_i < 0)
			return (false);
	}
	// これだと最後のコマンドがbuiltinコマンドであったとき，その終了ステータスを取得できない！
	// 最後のコマンドがbuiltinコマンドであったとき，その終了ステータスを格納するようにする！
	return (close_fd(pipex), get_final_cmd_exit_status(pipex, cmd_i));
}
