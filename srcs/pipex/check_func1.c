/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_func1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:14:49 by toshota           #+#    #+#             */
/*   Updated: 2023/11/20 10:50:56 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	*check_malloc(void *ptr)
{
	if (ptr == NULL)
	{
		put_error("failed to malloc\n");
		exit(1);
	}
	return (ptr);
}

int	check_open(int fd)
{
	if (fd == -1)
	{
		put_error("failed to open\n");
		return (false);
	}
	return (true);
}

int	check_close(int ret)
{
	if (ret < 0)
	{
		put_error("failed to close\n");
		return (false);
	}
	return (true);
}

int	check_pipe(int ret)
{
	if (ret < 0)
	{
		put_error("failed to create pipe\n");
		return (false);
	}
	return (true);
}

int	check_fork(pid_t child_pid)
{
	if (child_pid < 0)
	{
		put_error("failed to fork\n");
		return (false);
	}
	return (true);
}
