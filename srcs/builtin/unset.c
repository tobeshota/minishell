/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 17:36:07 by toshota           #+#    #+#             */
/*   Updated: 2023/12/09 10:12:48 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static bool	is_node_last(t_env *node)
{
	return (node->next == NULL);
}

static bool	is_node_first(t_env *node)
{
	return (node->prev == NULL);
}

int	exec_unset(char **cmd, t_env **env)
{
	int		i;
	t_env	*unseted_env;

	i = 0;
	while (cmd[++i])
	{
		if (check_identifier(cmd[i]) == false || is_under_bar(cmd[i]) == true)
			continue ;
		unseted_env = get_old_env_to_be_updated(cmd[i], *env);
		if (unseted_env == false)
			continue ;
		// if (is_node_last(unseted_env) == true)
		// 	unseted_env->prev->next = NULL;
		if (is_node_first(unseted_env) == true)
			// unseted_env->next->prev = NULL;
		{
			unseted_env = unseted_env->next;
			ft_nodedelone(&unseted_env->prev);
			ft_nodenext(env);
		}
		else
		{
			unseted_env->prev->next = unseted_env->next;
			unseted_env->next->prev = unseted_env->prev;
			ft_nodedelone(&unseted_env);
		}
		// ft_nodedelone(&unseted_env);
		ft_nodefirst(env);
	}
	return (true);
}
