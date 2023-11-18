/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:14:49 by toshota           #+#    #+#             */
/*   Updated: 2023/11/18 15:17:35 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// エラーメッセージ（）はここで出し，fd = -1を返すようにする
// bash: infile: Permission denied
// bash: infilea: No such file or directory
int	open_file(char *file, int file_type)
{
	int	fd;

	if (file_type == INFILE)
		fd = open(file, O_RDONLY);
	else if (file_type == INFILE_HERE_DOC)
		fd = open(file, O_RDWR | O_CREAT | O_APPEND,
				S_IRWXU | S_IRWXG | S_IRWXO);
	else if (file_type == OUTFILE_OVER_WRITING)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC,
				S_IRWXU | S_IRWXG | S_IRWXO);
	else if (file_type == OUTFILE_APEND)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND,
				S_IRWXU | S_IRWXG | S_IRWXO);
	else
		fd = -1;
	return (fd);
}

void	close_pipe(int *pipe_fd)
{
	check_close(close(pipe_fd[0]));
	check_close(close(pipe_fd[1]));
}

void	add_slash_eos(char ***path)
{
	char	*tmp;
	int		i;

	i = 0;
	while (path[0][i])
	{
		tmp = path[0][i];
		path[0][i] = check_malloc(ft_strjoin(path[0][i], "/"));
		free(tmp);
		i++;
	}
}

int	is_path_found(char *path)
{
	if (path == NULL)
	{
		put_error("PATH not found\n");
		return FALSE;
	}
	return TRUE;
}

void	wait_children(int cmd_i)
{
	int	i;

	i = 0;
	while (i < cmd_i)
	{
		check_wait(wait(NULL));
		i++;
	}
}
