/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_func3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:04:48 by toshota           #+#    #+#             */
/*   Updated: 2023/12/16 11:07:17 by toshota          ###   ########.fr       */
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
		return (false);
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

bool	check_is_dir(char *filename, int ret)
{
	if (ret == IS_A_DIRECTORY)
	{
		put_error_w_cmd(filename, "is a directory");
		g_global.error_num = 126;
		return (false);
	}
	return (true);
}

bool	check_cmd_exist(char *filename, int ret)
{
	if (ret == NOT_FOUND)
	{
		put_error_w_cmd(filename, "command not found");
		g_global.error_num = 127;
		return (false);
	}
	return (true);
}

bool	check_is_dot(int ret)
{
	if (ret == IS_DOT)
	{
		put_error("minishell: .: filename argument required\n.\
		: usage: . filename [arguments]\n");
		g_global.error_num = 2;
		return (false);
	}
	return (true);
}
