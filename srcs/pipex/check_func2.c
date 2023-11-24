/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_func2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 10:03:29 by toshota           #+#    #+#             */
/*   Updated: 2023/11/24 16:12:48 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool	check_dup(int ret)
{
	if (ret == -1)
	{
		put_error("failed to dup\n");
		return (false);
	}
	return (true);
}

bool	check_exec(int ret)
{
	if (ret == -1 || ret == false)
	{
		put_error("failed to execve\n");
		exit(126);
	}
	return (true);
}

bool	check_wait(int ret)
{
	if (ret == -1)
	{
		put_error("failed to wait\n");
		return (false);
	}
	return (true);
}

bool	check_unlink(int ret)
{
	if (ret == -1)
	{
		put_error("failed to unlink\n");
		return (false);
	}
	return (true);
}

bool	check_getenv(char *ptr)
{
	if (ptr == NULL)
	{
		put_error("failed to getenv\n");
		return (false);
	}
	return (true);
}
