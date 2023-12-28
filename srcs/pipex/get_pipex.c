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

static bool	init_pipex(char **argv, t_pipex *pipex, t_tools *tools)
{
	ft_bzero(pipex, sizeof(t_pipex));
	pipex->infile_fd = STDIN_FILENO;
	pipex->outfile_fd = STDOUT_FILENO;
	pipex->error_num = &tools->error_num;
	cp_argv(argv, pipex);
	return (rm_here_doc());
}

static void	malloc_multiple_pid(t_pipex *pipex)
{
	pipex->pid = (pid_t *)check_malloc(malloc \
	(sizeof(pid_t) * get_element_count(pipex->cmd_absolute_path)));
}

bool	get_pipex(char **argv, char **h_envp, t_pipex *pipex, t_tools *tools)
{
	if (init_pipex(argv, pipex, tools) == false)
		return (false);
	if (get_fd(pipex, pipex->argv, h_envp, tools) == false)
		return (false);
	if (get_cmd_absolute_path(h_envp, pipex) == false)
		return (false);
	malloc_multiple_pipe(pipex);
	malloc_multiple_pid(pipex);
	return (true);
}
