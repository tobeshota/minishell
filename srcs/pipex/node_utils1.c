/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobeshota <tobeshota@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 10:50:31 by toshota           #+#    #+#             */
/*   Updated: 2023/11/26 21:05:11 by tobeshota        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_env	*ft_nodenew(char *content)
{
	t_env	*newnode;

	newnode = (t_env *)check_malloc(malloc(sizeof(t_env)));
	newnode->content = check_malloc(ft_strdup(content));
	newnode->next = NULL;
	newnode->prev = NULL;
	return (newnode);
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

int	ft_nodesize(t_env *node)
{
	int		count;
	t_env	*ptr;

	count = 0;
	ptr = node;
	while (ptr != NULL)
	{
		ptr = ptr->next;
		count++;
	}
	return (count);
}
