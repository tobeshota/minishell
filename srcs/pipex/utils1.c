/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:14:49 by toshota           #+#    #+#             */
/*   Updated: 2023/12/09 10:49:40 by toshota          ###   ########.fr       */
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

char	*getenv_from_heap_envp(char **heap_envp, char *varname)
{
	int	he_i;
	int	varname_len;

	he_i = 0;
	varname_len = ft_strlen(varname);
	while (heap_envp[he_i] && ft_strlen(heap_envp[he_i]) >= varname_len &&  ft_strncmp(heap_envp[he_i], varname, varname_len))
		he_i++;
	return (heap_envp[he_i]);
}

char	*getenv_from_t_env(t_env *env, char *varname)
{
	while (env->next && ft_strncmp(env->content, varname, ft_strlen(varname)))
		ft_nodenext(&env);
	if (!ft_strncmp(env->content, varname, ft_strlen(varname)))
		return (env->content);
	else
		return (NULL);
}
