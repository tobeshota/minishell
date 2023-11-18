/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_func1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:14:49 by toshota           #+#    #+#             */
/*   Updated: 2023/11/18 16:15:58 by toshota          ###   ########.fr       */
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
		return (FALSE);
	}
	return (TRUE);
}

int	check_close(int ret)
{
	if (ret < 0)
	{
		put_error("failed to close\n");
		return (FALSE);
	}
	return (TRUE);
}

int	is_pipe_successfully(int ret)
{
	if (ret < 0)
	{
		put_error("failed to create pipe\n");
		return (FALSE);
	}
	return (TRUE);
}

int	is_fork_successfully(pid_t child_pid)
{
	if (child_pid < 0)
	{
		put_error("failed to fork\n");
		return (FALSE);
	}
	return (TRUE);
}
