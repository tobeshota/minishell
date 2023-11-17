/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pipex_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 01:18:05 by toshota           #+#    #+#             */
/*   Updated: 2023/11/18 01:27:32 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	malloc_multiple_pipe(int argc, char **argv,
		t_pipex_data *pipex_data)
{
	int	i;

	i = argc - argc;
	pipex_data->pipe_fd = (int **)malloc(sizeof(int *) * (get_cmd_count(argv)
				+ 1));
	check_malloc(pipex_data->pipe_fd);
	while (i < get_cmd_count(argv))
	{
		pipex_data->pipe_fd[i] = (int *)malloc(sizeof(int) * 2);
		check_malloc(pipex_data->pipe_fd);
		i++;
	}
	pipex_data->pipe_fd[i] = NULL;
}

void	get_pipex_data(int argc, char **argv, char **envp,
		t_pipex_data *pipex_data)
{
	get_cmd_absolute_path(argv, envp, pipex_data);
	malloc_multiple_pipe(argc, argv, pipex_data);
}
