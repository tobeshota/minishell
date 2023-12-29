/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:14:49 by toshota           #+#    #+#             */
/*   Updated: 2023/12/29 10:19:28 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_file(char *file, int file_type)
{
	int		fd;
	char	*file_wo_encloser;

	file_wo_encloser = omit_str(file, "\'\"");
	if (file_type == INFILE)
		fd = open(file_wo_encloser, O_RDONLY);
	else if (file_type == INFILE_HERE_DOC)
		fd = open(file_wo_encloser, O_RDWR | O_CREAT | O_APPEND,
				S_IRWXU | S_IRWXG | S_IRWXO);
	else if (file_type == OUTFILE_OVER_WRITING)
		fd = open(file_wo_encloser, O_WRONLY | O_CREAT | O_TRUNC,
				S_IRWXU | S_IRWXG | S_IRWXO);
	else if (file_type == OUTFILE_APEND)
		fd = open(file_wo_encloser, O_WRONLY | O_CREAT | O_APPEND,
				S_IRWXU | S_IRWXG | S_IRWXO);
	else
		fd = -1;
	return (free(file_wo_encloser), fd);
}

int	close_file(int fd, int default_fd)
{
	if (fd != default_fd && fd >= 0)
		return (close(fd));
	return (0);
}

bool	close_pipe(int *pipe_fd)
{
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	return (true);
}

bool	is_path_found(char *path)
{
	if (path == NULL)
	{
		put_error("PATH not found\n");
		return (false);
	}
	return (true);
}

int	wait_child(int cmd_i, t_pipex *pipex)
{
	int		i;
	int		ret;
	int		status;
	int		final_cmd_exit_status;

	i = 0;
	final_cmd_exit_status = 0;
	while (i < cmd_i)
	{
		ret = waitpid(pipex->pid[i], &status, 0);
		final_cmd_exit_status = get_child_exit_status(status);
		if (check_wait(ret) == false)
			return (false);
		i++;
	}
	return (final_cmd_exit_status);
}
