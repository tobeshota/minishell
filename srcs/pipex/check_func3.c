/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_func3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:04:48 by toshota           #+#    #+#             */
/*   Updated: 2023/12/28 15:24:34 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool	check_opendir(DIR *dir, char *path)
{
	if (dir == NULL)
		return (put_error_w_file(path, strerror(errno)), false);
	return (true);
}

bool	check_closedir(int ret)
{
	if (ret == -1)
		return (ft_putendl_fd(strerror(errno), STDERR_FILENO), false);
	return (true);
}

bool	check_execve(int ret, char *cmd, t_pipex *pipex)
{
	if (ret == -1 || ret == false)
	{
		if (errno != 0)
			put_error_w_cmd(cmd, strerror(errno));
		else
			put_error("failed to execve\n");
		*pipex->error_num = 126;
		return (false);
	}
	return (true);
}

bool	check_exec_builtin(int ret, char *cmd, t_pipex *pipex)
{
	(void)cmd;
	if (ret == -1 || ret == false)
	{
		// if (errno != 0)
		// 	put_error_w_cmd(cmd, strerror(errno));
		// else
		// 	put_error("failed to exec_builtin\n");
		if (*pipex->error_num == 0)
			*pipex->error_num = 126;
		return (false);
	}
	return (true);
}
