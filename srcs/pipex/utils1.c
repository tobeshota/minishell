/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:14:49 by toshota           #+#    #+#             */
/*   Updated: 2023/12/05 20:47:53 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	get_larger(size_t n1, size_t n2)
{
	if (n1 > n2)
		return (n1);
	return (n2);
}

void	get_order(t_env *node)
{
	t_env	*test;

	test = node;
	while (node)
	{
		node->order = 1;
		while (test->next)
		{
			if (ft_strncmp(node->content, test->content,
					get_larger(ft_strlen(node->content),
						ft_strlen(test->content))) > 0)
				node->order++;
			ft_nodenext(&test);
		}
		if (ft_strncmp(node->content, test->content,
				get_larger(ft_strlen(node->content),
					ft_strlen(test->content))) > 0)
			node->order++;
		node = node->next;
		ft_nodefirst(&test);
	}
}
