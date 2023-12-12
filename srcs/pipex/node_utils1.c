/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 10:50:31 by toshota           #+#    #+#             */
/*   Updated: 2023/12/12 15:08:11 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_env	*ft_nodenew(char *content)
{
	t_env	*newnode;

	newnode = (t_env *)check_malloc(malloc(sizeof(t_env)));
	newnode->content = check_malloc(ft_strdup(content));
	newnode->order = 0;
	newnode->next = NULL;
	newnode->prev = NULL;
	return (newnode);
}

void	ft_nodeadd_front(t_env **node, t_env *new)
{
	if (node == NULL || new == NULL)
		return ;
	new->next = *node;
	if (*node)
		(*node)->prev = new;
	*node = new;
}

void	ft_nodeadd_back(t_env **node, t_env *new)
{
	t_env	*node_last;

	if (node == NULL || new == NULL)
		return ;
	if (*node == NULL)
	{
		*node = new;
		new->prev = *node;
		return ;
	}
	node_last = ft_nodelast(*node);
	new->prev = node_last;
	node_last->next = new;
}

void	ft_nodedelone(t_env **node)
{
	free((*node)->content);
	(*node)->content = NULL;
	free(*node);
	*node = NULL;
}

void	ft_nodeclear(t_env **node)
{
	t_env	*tmp;

	if (*node == NULL)
		return ;
	while (*node)
	{
		tmp = (*node)->next;
		ft_nodedelone(node);
		*node = tmp;
	}
}
