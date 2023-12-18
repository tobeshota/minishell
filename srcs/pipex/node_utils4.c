/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_utils4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 23:47:46 by toshota           #+#    #+#             */
/*   Updated: 2023/12/18 23:49:18 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	unset_first_node(t_env **unseted_env, t_env **env)
{
	*unseted_env = (*unseted_env)->next;
	ft_nodedelone(&(*unseted_env)->prev);
	ft_nodenext(env);
}

void	unset_last_node(t_env **unseted_env)
{
	*unseted_env = (*unseted_env)->prev;
	ft_nodedelone(&(*unseted_env)->next);
}

void	unset_middle_node(t_env *unseted_env)
{
	unseted_env->prev->next = unseted_env->next;
	unseted_env->next->prev = unseted_env->prev;
	ft_nodedelone(&unseted_env);
}
