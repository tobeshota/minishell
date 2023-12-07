/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 15:36:11 by toshota           #+#    #+#             */
/*   Updated: 2023/12/07 20:58:42 by toshota          ###   ########.fr       */
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

void	node_to_array(t_env *env, char ***envp)
{
	int	env_i;

	env_i = 0;
	while (envp[0][env_i] && env && env->next)
	{
		ft_strlcpy \
		(envp[0][env_i], env->content, ft_strlen(env->content) + 1);
		ft_nodenext(&env);
		env_i++;
	}
}
