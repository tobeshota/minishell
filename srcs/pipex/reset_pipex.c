/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 21:55:41 by toshota           #+#    #+#             */
/*   Updated: 2023/12/09 21:56:00 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool	reset_pipex(t_pipex *pipex, int cmd_i)
{
	pipex->infile_fd = STDIN_FILENO;
	pipex->outfile_fd = STDOUT_FILENO;
	if (rm_here_doc() == false)
		return (false);
	if (cmd_i > 0 && close_pipe(pipex->pipe_fd[cmd_i - 1]) == false)
		return (false);
	return (true);
}
