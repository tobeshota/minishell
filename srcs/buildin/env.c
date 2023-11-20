/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:39:21 by toshota           #+#    #+#             */
/*   Updated: 2023/11/20 14:24:23 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildin.h"

int	execve_env(char **envp, t_pipex_data *pipex_data)
{
	int	i;

	i = -1;
	while (envp[++i])
		ft_putendl_fd(envp[i], pipex_data->outfile_fd);
	return (true);
}
