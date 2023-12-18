/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 17:36:07 by toshota           #+#    #+#             */
/*   Updated: 2023/12/18 12:21:06 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

bool	is_node_last(t_env *node)
{
	return (node->next == NULL);
}

void	unset_last_node(t_env *unseted_env)
{
	unseted_env->prev->next = NULL;
	ft_nodedelone(&unseted_env);
}

bool	is_node_first(t_env *node)
{
	return (node->prev == NULL);
}

void	unset_first_node(t_env *unseted_env, t_env **env)
{
	unseted_env = unseted_env->next;
	ft_nodedelone(&unseted_env->prev);
	ft_nodenext(env);
}

int	exec_unset(char **cmd, t_env **env, t_pipex *pipex)
{
	int		i;
	t_env	*unseted_env;

	i = 0;
	while (cmd[++i])
	{
		if (!check_identifier(cmd[i], pipex) || is_under_bar(cmd[i]))
			continue ;
		unseted_env = get_old_env_to_be_updated(cmd[i], *env);
		if (unseted_env == false)
			continue ;
		if (is_node_last(unseted_env) == true)
			unset_last_node(unseted_env);
		else if (is_node_first(unseted_env) == true)
			unset_first_node(unseted_env, env);
		else
		{
			unseted_env->prev->next = unseted_env->next;
			unseted_env->next->prev = unseted_env->prev;
			ft_nodedelone(&unseted_env);
		}
		ft_nodefirst(env);
	}
	return (true);
}
