/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:39:21 by toshota           #+#    #+#             */
/*   Updated: 2023/11/25 21:30:30 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	exec_env(t_env **env_node, t_pipex_data *pipex_data)
{
	if (env_node == NULL)
		return (false);
	while ((*env_node)->next)
	{
		ft_putendl_fd((*env_node)->content, pipex_data->outfile_fd);
		ft_nodenext(env_node);
	}
	ft_putendl_fd((*env_node)->content, pipex_data->outfile_fd);
	ft_nodefirst(env_node);
	return (true);
}
