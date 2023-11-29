/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:39:21 by toshota           #+#    #+#             */
/*   Updated: 2023/11/29 11:23:24 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static bool	is_identifier_definition_exist(char *content)
{
	return (ft_strchr(content, '='));
}

int	exec_env(t_env **env, t_pipex *pipex)
{
	if (env == NULL)
		return (false);
	while ((*env)->next)
	{
		if (is_identifier_definition_exist((*env)->content))
			ft_putendl_fd((*env)->content, pipex->outfile_fd);
		ft_nodenext(env);
	}
	if (is_identifier_definition_exist((*env)->content))
		ft_putendl_fd((*env)->content, pipex->outfile_fd);
	ft_nodefirst(env);
	return (true);
}
