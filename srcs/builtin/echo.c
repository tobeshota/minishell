/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:39:21 by toshota           #+#    #+#             */
/*   Updated: 2023/11/24 11:10:16 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	exec_echo(char **cmd, t_pipex_data *pipex_data)
{
	int	cmd_i;

	if (cmd[1] && is_match(cmd[1], "-n") == true)
	{
		cmd_i = 2;
		while (cmd[cmd_i])
		{
			ft_putstr_fd(cmd[cmd_i], pipex_data->outfile_fd);
			if (cmd[++cmd_i])
				ft_putchar_fd(' ', pipex_data->outfile_fd);
		}
	}
	else
	{
		cmd_i = 1;
		while (cmd[cmd_i])
		{
			ft_putstr_fd(cmd[cmd_i], pipex_data->outfile_fd);
			if (cmd[++cmd_i])
				ft_putchar_fd(' ', pipex_data->outfile_fd);
		}
		ft_putchar_fd('\n', pipex_data->outfile_fd);
	}
	return (true);
}
