/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:39:21 by toshota           #+#    #+#             */
/*   Updated: 2023/12/28 14:57:41 by toshota          ###   ########.fr       */
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
	while (true)
	{
		if (is_identifier_definition_exist((*env)->content))
			ft_putendl_fd((*env)->content, pipex->outfile_fd);
		if ((*env)->next == NULL)
			break ;
		ft_nodenext(env);
	}
	return (ft_nodefirst(env), true);
}
