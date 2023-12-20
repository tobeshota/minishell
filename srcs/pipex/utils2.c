/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:14:49 by toshota           #+#    #+#             */
/*   Updated: 2023/12/20 11:29:44 by toshota          ###   ########.fr       */
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
	if (fd != default_fd)
		return (close(fd));
	return (0);
}

bool	close_pipe(int *pipe_fd)
{
	if(check_close(close(pipe_fd[0])) == false)
		return (false);
	if(check_close(close(pipe_fd[1])) == false)
		return (false);
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

bool	wait_children(int cmd_i, t_pipex *pipex)
{
	int	i;
	int	status;
	int	ret;

	i = 0;
	while (i < cmd_i)
	{
		ret = wait(&status);
		*pipex->error_num = get_child_exit_status(status);
		if (check_wait(ret) == false)
			return (false);
		i++;
	}
	return (true);
}
