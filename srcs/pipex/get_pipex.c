/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pipex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 01:18:05 by toshota           #+#    #+#             */
/*   Updated: 2023/11/25 21:43:07 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static bool	init_pipex(t_pipex *pipex)
{
	ft_bzero(pipex, sizeof(t_pipex));
	pipex->infile_fd = STDIN_FILENO;
	pipex->outfile_fd = STDOUT_FILENO;
	return (rm_here_doc());
}

bool	get_pipex(char **argv, char **h_envp, t_pipex *pipex)
{
	if (init_pipex(pipex) == false)
		return (false);
	cp_argv(argv, pipex);
	if (get_fd(pipex, pipex->argv, h_envp) == false)
		return (false);
	if (get_cmd_absolute_path(h_envp, pipex) == false)
		return (false);
	malloc_multiple_pipe(pipex);
	return (true);
}
