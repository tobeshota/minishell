/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:14:49 by toshota           #+#    #+#             */
/*   Updated: 2023/11/25 21:56:14 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool	is_fd_default(int fd, int default_fd)
{
	return (fd == default_fd);
}

bool	is_limitter(char **argv, int arg_i)
{
	return (arg_i > 0 && is_specified_here_doc(argv[arg_i - 1]));
}

bool	is_cmd(char **argv, int arg_i)
{
	return (is_file_exectable(argv[arg_i]) \
	|| (!is_file_exist(argv[arg_i]) \
	&& !is_specified_operators(argv[arg_i]) \
	&& !is_limitter(argv, arg_i)));
}

bool	is_cmd_relative_path(char ***cmd_absolute_path, int cmd_i)
{
	return (cmd_absolute_path[0][cmd_i][0] != '/'
		&& ft_strchr(&cmd_absolute_path[0][cmd_i][1], '/'));
}

bool	is_cmd_alreadly_absollute_path(char ***cmd_absolute_path, int cmd_i)
{
	return (cmd_absolute_path[0][cmd_i][0] == '/'
		&& ft_strchr(&cmd_absolute_path[0][cmd_i][1], '/'));
}
