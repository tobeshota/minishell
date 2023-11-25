/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:39:21 by toshota           #+#    #+#             */
/*   Updated: 2023/11/25 22:40:18 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	exec_pwd(t_pipex *pipex)
{
	char	pwd[PATH_MAX];

	if (getcwd(pwd, PATH_MAX) == NULL)
		return (false);
	ft_putendl_fd(pwd, pipex->outfile_fd);
	return (true);
}
