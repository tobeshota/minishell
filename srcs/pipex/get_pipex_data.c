/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pipex_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 01:18:05 by toshota           #+#    #+#             */
/*   Updated: 2023/11/20 11:14:31 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static bool	malloc_multiple_pipe(int argc, char **argv,
		t_pipex_data *pipex_data)
{
	int	i;

	i = argc - argc;
	pipex_data->pipe_fd = (int **)check_malloc(malloc(sizeof(int *)
				* (get_cmd_count(argv) + 1)));
	while (i < get_cmd_count(argv))
	{
		pipex_data->pipe_fd[i] = (int *)check_malloc(malloc(sizeof(int) * 2));
		i++;
	}
	pipex_data->pipe_fd[i] = NULL;
	return (true);
}

static void	init_pipex_data(t_pipex_data *pipex_data)
{
	ft_bzero(pipex_data, sizeof(t_pipex_data));
	pipex_data->infile_fd = STDIN_FILENO;
	pipex_data->outfile_fd = STDOUT_FILENO;
}

bool	get_pipex_data(int argc, char **argv, char **envp,
		t_pipex_data *pipex_data)
{
	init_pipex_data(pipex_data);
	if (get_infile_fd(pipex_data, 0, argv) == false)
		return (false);
	if (get_outfile_fd(pipex_data, 0, argv) == false)
		return (false);
	if (get_cmd_absolute_path(argv, envp, pipex_data) == false)
		return (false);
	if (malloc_multiple_pipe(argc, argv, pipex_data) == false)
		return (false);
	return (true);
}
