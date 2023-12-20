/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 21:55:41 by toshota           #+#    #+#             */
/*   Updated: 2023/12/21 02:10:47 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	if (get_fd(pipex, pipex->argv + \
	get_arg_i(cmd_i + 1, pipex->argv), h_envp, tools) == false)
		return (false);
	return (true);
}
