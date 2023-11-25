/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pipex_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 01:18:05 by toshota           #+#    #+#             */
/*   Updated: 2023/11/25 19:29:51 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int get_builtin_cmd_count(t_pipex_data *pipex_data)
{
	int	cmd_i;
	int	builtin_cmd_count;

	cmd_i = 0;
	builtin_cmd_count = 0;
	while (pipex_data->cmd_absolute_path[cmd_i])
	{
		if (is_cmd_builtin(pipex_data->cmd_absolute_path[cmd_i]))
			builtin_cmd_count++;
		cmd_i++;
	}
	return (builtin_cmd_count);
}

int	get_pipe_count(char **argv)
{
	int	arg_i;
	int	pipe_count;

	arg_i = 0;
	pipe_count = 0;
	while (argv[arg_i])
	{
		if (is_specified_pipe(argv[arg_i]))
			pipe_count++;
		arg_i++;
	}
	return (pipe_count);
}

static void	malloc_multiple_pipe(char **argv, t_pipex_data *pipex_data)
{
	int	i;
	int	pipe_count;

	i = 0;
	pipe_count = get_pipe_count(argv);
	pipex_data->pipe_fd = (int **)check_malloc(malloc(sizeof(int *)
				* pipe_count));
	while (i < pipe_count)
	{
		pipex_data->pipe_fd[i] = (int *)check_malloc(malloc(sizeof(int) * 2));
		i++;
	}
	pipex_data->pipe_fd[i] = NULL;
}

static void	init_pipex_data(t_pipex_data *pipex_data)
{
	ft_bzero(pipex_data, sizeof(t_pipex_data));
	pipex_data->infile_fd = STDIN_FILENO;
	pipex_data->outfile_fd = STDOUT_FILENO;
}

bool	get_pipex_data(char **argv, t_pipex_data *pipex_data)
{
	init_pipex_data(pipex_data);
	if (get_infile_fd(pipex_data, 0, argv) == false)
		return (false);
	if (get_outfile_fd(pipex_data, 0, argv) == false)
		return (false);
	if (get_cmd_absolute_path(argv, pipex_data) == false)
		return (false);
	malloc_multiple_pipe(argv, pipex_data);
	return (true);
}
