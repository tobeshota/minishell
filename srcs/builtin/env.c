/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:39:21 by toshota           #+#    #+#             */
/*   Updated: 2023/11/25 22:06:55 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	exec_env(t_env **env, t_pipex_data *pipex_data)
{
	if (env == NULL)
		return (false);
	while ((*env)->next)
	{
		ft_putendl_fd((*env)->content, pipex_data->outfile_fd);
		ft_nodenext(env);
	}
	ft_putendl_fd((*env)->content, pipex_data->outfile_fd);
	ft_nodefirst(env);
	return (true);
}
