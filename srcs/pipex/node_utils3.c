/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 17:36:07 by toshota           #+#    #+#             */
/*   Updated: 2023/12/18 21:08:20 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool	is_node_last(t_env *node)
{
	return (node->next == NULL);
}

bool	is_node_first(t_env *node)
{
	return (node->prev == NULL);
}

void	unset_first_node(t_env **unseted_env, t_env **env)
{
	*unseted_env = (*unseted_env)->next;
	ft_nodedelone(&(*unseted_env)->prev);
	ft_nodenext(env);
}

void	unset_last_node(t_env **unseted_env)
{
	(*unseted_env)->prev->next = NULL;
	ft_nodedelone(unseted_env);
}

void	unset_middle_node(t_env *unseted_env)
{
	unseted_env->prev->next = unseted_env->next;
	unseted_env->next->prev = unseted_env->prev;
	ft_nodedelone(&unseted_env);
}
