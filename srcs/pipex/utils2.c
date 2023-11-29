/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:14:49 by toshota           #+#    #+#             */
/*   Updated: 2023/11/29 12:51:46 by toshota          ###   ########.fr       */
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

bool	close_pipe(int *pipe_fd)
{
	if (check_close(close(pipe_fd[0])) == false)
		return (false);
	if (check_close(close(pipe_fd[1])) == false)
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

bool	wait_children(int cmd_i)
{
	int	i;

	i = 0;
	while (i < cmd_i)
	{
		if (check_wait(wait(NULL)) == false)
			return (false);
		i++;
	}
	return (true);
}

size_t get_larger(size_t n1, size_t n2)
{
	if(n1 > n2)
		return n1;
	return n2;
}

void	get_order(t_env *node)
{
	t_env	*test;

	test = node;
	// while (node->next)
	while (node)
	{
		node->order = 1;
		while (test->next)
		{
			// if (ft_strncmp(node->content, test->content, ft_strlen(test->content)) > 0)
			if (ft_strncmp(node->content, test->content, get_larger(ft_strlen(node->content), ft_strlen(test->content))) > 0)
				node->order++;
			ft_nodenext(&test);
		}
		// if (ft_strncmp(node->content, test->content, ft_strlen(test->content)) > 0)
		if (ft_strncmp(node->content, test->content, get_larger(ft_strlen(node->content), ft_strlen(test->content))) > 0)
			node->order++;
		// ft_nodenext(&node);
		node = node->next;
		ft_nodefirst(&test);
	}
}
