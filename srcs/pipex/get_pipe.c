/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 13:06:15 by toshota           #+#    #+#             */
/*   Updated: 2023/12/14 13:07:43 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	malloc_multiple_pipe(t_pipex *pipex)
{
	int	i;
	int	pipe_count;

	i = 0;
	pipe_count = get_pipe_count(pipex->argv);
	if (pipe_count == 0)
		return ;
	pipex->pipe_fd = (int **)check_malloc \
	(malloc(sizeof(int *) * (pipe_count + 1)));
	while (i < pipe_count)
	{
		pipex->pipe_fd[i] = (int *)check_malloc(malloc(sizeof(int) * 2));
		i++;
	}
	pipex->pipe_fd[i] = NULL;
}

bool	get_pipe(t_pipex *pipex, int cmd_i)
{
	return (check_pipe(pipe(pipex->pipe_fd[cmd_i])));
}
