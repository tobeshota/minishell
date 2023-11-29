/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:39:21 by toshota           #+#    #+#             */
/*   Updated: 2023/11/29 13:17:04 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	exec_export(char **cmd, t_env **env, t_pipex *pipex)
{
	int		i;

	i = 1;
	if (cmd[i])
	{
		while (cmd[i])
		{
			if (get_old_env_to_be_updated(cmd[i], *env) == NULL)
				add_new_value(cmd[i], env);
			else
				update_value(cmd[i], env);
			ft_nodefirst(env);
			i++;
		}
	}
	else
	{
		get_order(*env);
		show_env(env, pipex);
	}
	return (ft_nodefirst(env), true);
}
