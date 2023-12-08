/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 15:36:11 by toshota           #+#    #+#             */
/*   Updated: 2023/12/08 23:32:13 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_env	*array_to_node(char **envp)
{
	t_env	*node;
	t_env	*new;
	int		env_i;

	env_i = 0;
	if (envp == NULL || envp[0] == NULL)
		return (NULL);
	while (envp[env_i])
	{
		new = check_malloc(ft_nodenew(envp[env_i]));
		if (env_i == 0)
			node = new;
		else
			ft_nodeadd_back(&node, new);
		env_i++;
	}
	return (node);
}

char	**node_to_array(t_env *env)
{
	int		env_i;
	char	**heap_envp;

	env_i = 0;
	heap_envp = (char **)check_malloc(malloc(sizeof(char *)
				* ft_nodesize(env)));
	while (env->next)
	{
		heap_envp[env_i++] = check_malloc(ft_strdup(env->content));
		ft_nodenext(&env);
	}
	heap_envp[env_i++] = check_malloc(ft_strdup(env->content));
	heap_envp[env_i] = NULL;
	ft_nodefirst(&env);
	return (heap_envp);
}
