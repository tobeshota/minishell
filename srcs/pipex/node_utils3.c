/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 17:36:07 by toshota           #+#    #+#             */
/*   Updated: 2023/12/19 00:13:43 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_nodeswap(t_env *n1, t_env *n2)
{
	char	*tmp_content;
	int		tmp_order;

	tmp_content = n1->content;
	n1->content = n2->content;
	n2->content = tmp_content;
	tmp_order = n1->order;
	n1->order = n2->order;
	n2->order = tmp_order;
}

void	ft_nodesort(t_env **node)
{
	t_env	*head;

	while (true)
	{
		head = *node;
		while (true)
		{
			if (head->next == NULL)
				break ;
			else if (head->order > head->next->order)
				ft_nodeswap(head, head->next);
			head = head->next;
		}
		if ((*node)->next == NULL)
			break ;
		*node = (*node)->next;
	}
	ft_nodefirst(node);
}

bool	is_node_first(t_env *node)
{
	return (node->prev == NULL);
}

bool	is_node_last(t_env *node)
{
	return (node->next == NULL);
}

bool	is_node_only_one(t_env *node)
{
	return (is_node_first(node) && is_node_last(node));
}
