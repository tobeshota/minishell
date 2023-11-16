/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_func2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 10:03:29 by toshota           #+#    #+#             */
/*   Updated: 2023/11/13 16:57:55 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	check_dup(int ret)
{
	if (ret == -1)
	{
		put_error("failed to dup\n");
		exit(1);
	}
}

void	check_execve(int ret)
{
	if (ret == -1)
	{
		put_error("failed to execve\n");
		exit(1);
	}
}

void	check_wait(int ret)
{
	if (ret == -1)
	{
		put_error("failed to wait\n");
		exit(1);
	}
}

void	check_unlink(int ret)
{
	if (ret == -1)
	{
		put_error("failed to unlink\n");
		exit(1);
	}
}
