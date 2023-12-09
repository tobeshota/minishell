/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_func3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:04:48 by toshota           #+#    #+#             */
/*   Updated: 2023/12/09 19:22:10 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool	check_execve(int ret, char *cmd)
{
	if (ret == -1 || ret == false)
	{
		if (errno != 0)
			put_error_w_cmd(cmd, strerror(errno));
		else
			put_error("failed to execve\n");
		g_global.error_num = 126;
		exit(126);
	}
	return (true);
}

bool	check_exec_builtin(int ret, char *cmd)
{
	if (ret == -1 || ret == false)
	{
		if (errno != 0)
			put_error_w_cmd(cmd, strerror(errno));
		else
			put_error("failed to exec_builtin\n");
		g_global.error_num = 126;
		return (false);
	}
	return (true);
}
