/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 15:36:11 by toshota           #+#    #+#             */
/*   Updated: 2023/12/10 22:27:11 by toshota          ###   ########.fr       */
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
	char	**h_envp;

	env_i = 0;
	h_envp = (char **)check_malloc \
	(malloc(sizeof(char *) * (ft_nodesize(env) + 1)));
	while (env->next)
	{
		h_envp[env_i] = check_malloc(ft_strdup(env->content));
		env_i++;
		ft_nodenext(&env);
	}
	h_envp[env_i] = check_malloc(ft_strdup(env->content));
	env_i++;
	h_envp[env_i] = NULL;
	ft_nodefirst(&env);
	return (h_envp);
}
