/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pipex_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 11:45:11 by toshota           #+#    #+#             */
/*   Updated: 2023/12/29 12:14:22 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_final_cmd_exit_status(t_pipex *pipex, int cmd_i)
{
	int	final_builtin_cmd_exit_status;
	int	final_execve_cmd_exit_status;

	final_execve_cmd_exit_status = \
	wait_child(cmd_i - count_builtin(pipex), pipex);
	final_builtin_cmd_exit_status = *pipex->error_num;
	if (is_cmd_builtin(pipex->cmd_absolute_path[cmd_i - 1]))
		*pipex->error_num = final_builtin_cmd_exit_status;
	else
		*pipex->error_num = final_execve_cmd_exit_status;
	return (*pipex->error_num == 0);
}

bool	check_iofd(t_pipex *pipex)
{
	if (pipex->infile_fd == -1)
	{
		*pipex->error_num = 1;
		return (false);
	}
	if (pipex->outfile_fd == -1)
	{
		*pipex->error_num = 1;
		return (false);
	}
	return (true);
}

bool	reset_pipex(char **h_envp, t_pipex *pipex, t_tools *tools, int cmd_i)
{
	if (close_fd(pipex) == false)
		return (false);
	pipex->infile_fd = STDIN_FILENO;
	pipex->outfile_fd = STDOUT_FILENO;
	if (rm_here_doc() == false)
		return (false);
	if (cmd_i > 0 && close_pipe(pipex->pipe_fd[cmd_i - 1]) == false)
		return (false);
	get_fd(pipex, pipex->argv + get_arg_i(cmd_i + 1, pipex->argv), \
	h_envp, tools);
	return (true);
}
