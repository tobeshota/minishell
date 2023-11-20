/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_func2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 10:03:29 by toshota           #+#    #+#             */
/*   Updated: 2023/11/20 10:50:56 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_dup(int ret)
{
	if (ret == -1)
	{
		put_error("failed to dup\n");
		return (false);
	}
	return (true);
}

int	check_execve(int ret)
{
	if (ret == -1)
	{
		put_error("failed to execve\n");
		return (false);
	}
	return (true);
}

int	check_wait(int ret)
{
	if (ret == -1)
	{
		put_error("failed to wait\n");
		return (false);
	}
	return (true);
}

int	check_unlink(int ret)
{
	if (ret == -1)
	{
		put_error("failed to unlink\n");
		return (false);
	}
	return (true);
}
