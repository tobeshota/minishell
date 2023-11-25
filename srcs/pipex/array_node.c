/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 10:50:31 by toshota           #+#    #+#             */
/*   Updated: 2023/11/25 14:57:41 by toshota          ###   ########.fr       */
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

void	ft_nodefirst(t_env **node)
{
	if (node == NULL || *node == NULL)
		return ;
	while ((*node)->prev != NULL)
		*node = (*node)->prev;
}

// env_node = array_to_node(envp);
t_env	*array_to_node(char **envp)
{
	t_env	*node;
	t_env	*new;
	int		env_i;

	env_i = 1;
	if (envp == NULL)
		return NULL;
	while (envp[env_i])
	{
		new = check_malloc(ft_nodenew(envp[env_i]));
		if (env_i == 1)
			node = new;
		else
			ft_nodeadd_back(&node, new);
		env_i++;
	}
	return node;
}

char	***node_to_array(t_env *env_node)
{
	return (NULL);
}
