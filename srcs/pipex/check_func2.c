/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_func2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 10:03:29 by toshota           #+#    #+#             */
/*   Updated: 2023/11/18 16:16:00 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_dup(int ret)
{
	if (ret == -1)
	{
		put_error("failed to dup\n");
		return (FALSE);
	}
	return (TRUE);
}

int	check_execve(int ret)
{
	if (ret == -1)
	{
		put_error("failed to execve\n");
		return (FALSE);
	}
	return (TRUE);
}

int	check_wait(int ret)
{
	if (ret == -1)
	{
		put_error("failed to wait\n");
		return (FALSE);
	}
	return (TRUE);
}

int	is_success_to_unlink(int ret)
{
	if (ret == -1)
	{
		put_error("failed to unlink\n");
		return (FALSE);
	}
	return (TRUE);
}
