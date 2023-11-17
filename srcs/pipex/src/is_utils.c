/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:14:49 by toshota           #+#    #+#             */
/*   Updated: 2023/11/18 01:19:14 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	is_fd_default(int fd, int default_fd)
{
	return (fd == default_fd);
}

int	is_limitter(char **argv, int arg_i)
{
	return (arg_i > 0 && is_specified_here_doc(argv[arg_i - 1]));
}

int	is_cmd(char **argv, int arg_i)
{
	return (!access(argv[arg_i], X_OK) || (access(argv[arg_i], F_OK)
			&& !is_specified_operators(argv[arg_i]) && !is_limitter(argv,
				arg_i)));
}

int	is_cmd_relative_path(char ***cmd_absolute_path, int cmd_i)
{
	if (cmd_absolute_path[0][cmd_i][0] != '/'
		&& ft_strchr(&cmd_absolute_path[0][cmd_i][1], '/'))
		return (TRUE);
	return (FALSE);
}

int	is_cmd_alreadly_absollute_path(char ***cmd_absolute_path, int cmd_i)
{
	if (cmd_absolute_path[0][cmd_i][0] == '/'
		&& ft_strchr(&cmd_absolute_path[0][cmd_i][1], '/'))
		return (TRUE);
	return (FALSE);
}
