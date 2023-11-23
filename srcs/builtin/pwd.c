/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:39:21 by toshota           #+#    #+#             */
/*   Updated: 2023/11/23 19:08:46 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	exec_pwd(char **envp, t_pipex_data *pipex_data)
{
	char	**pwd;

	if (get_pwd(&pwd, envp) == false)
		return (false);
	write(pipex_data->outfile_fd, pwd[0], ft_strlen(pwd[0]) - 1);
	ft_putchar_fd('\n', pipex_data->outfile_fd);
	all_free_tab(pwd);
	return (true);
}
