/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 15:36:11 by toshota           #+#    #+#             */
/*   Updated: 2023/11/25 21:43:37 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_env	*array_to_node(char **envp)
{
	t_env	*node;
	t_env	*new;
	int		env_i;

	env_i = 0;
	if (envp == NULL)
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

void	node_to_array(t_env *env_node, char ***envp)
{
	int	env_i;

	env_i = 0;
	while (envp[0][env_i] && env_node && env_node->next)
	{
		ft_strlcpy \
		(envp[0][env_i], env_node->content, ft_strlen(env_node->content) + 1);
		ft_nodenext(&env_node);
		env_i++;
	}
}
