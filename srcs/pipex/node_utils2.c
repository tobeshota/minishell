/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 10:50:31 by toshota           #+#    #+#             */
/*   Updated: 2023/11/25 15:37:32 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_nodefirst(t_env **node)
{
	if (node == NULL || *node == NULL)
		return ;
	while ((*node)->prev != NULL)
		*node = (*node)->prev;
}

void	ft_nodenext(t_env **node)
{
	if (node == NULL || *node == NULL)
		return ;
	if (*node != NULL)
		*node = (*node)->next;
}

t_env	*ft_nodelast(t_env *node)
{
	t_env	*result;

	if (node == NULL)
		return (NULL);
	result = node;
	while (result->next != NULL)
		result = result->next;
	return (result);
}
