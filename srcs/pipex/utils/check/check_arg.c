/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 12:01:35 by toshota           #+#    #+#             */
/*   Updated: 2023/12/29 12:04:17 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool	check_is_dir(char *filename, int ret, t_pipex *pipex)
{
	if (ret == IS_A_DIRECTORY)
	{
		put_error_w_cmd(filename, "is a directory");
		*pipex->error_num = 126;
		return (false);
	}
	return (true);
}

bool	check_cmd_exist(char *filename, int ret, t_pipex *pipex)
{
	if (ret == NOT_FOUND)
	{
		put_error_w_cmd(filename, "command not found");
		*pipex->error_num = 127;
		return (false);
	}
	return (true);
}

bool	check_is_dot(int ret, t_pipex *pipex)
{
	if (ret == IS_DOT)
	{
		put_error("minishell: .: filename argument required\n.\
		: usage: . filename [arguments]\n");
		*pipex->error_num = 2;
		return (false);
	}
	return (true);
}
