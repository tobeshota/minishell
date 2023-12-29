/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:14:49 by toshota           #+#    #+#             */
/*   Updated: 2023/12/20 10:55:19 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#define EQUAL 1

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

char	*getenv_from_h_envp(char **h_envp, char *varname)
{
	int	he_i;
	int	varname_len;

	he_i = 0;
	varname_len = ft_strlen(varname);
	while (h_envp[he_i])
	{
		if (ft_strlen(h_envp[he_i]) > 0 && !ft_strncmp(h_envp[he_i], varname,
				varname_len))
			return (h_envp[he_i] + ft_strlen(varname) + EQUAL);
		he_i++;
	}
	return (NULL);
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

int	ft_strrncmp(const char *s1, const char *s2, size_t n)
{
	size_t	s1_i;
	size_t	s2_i;
	size_t	count;

	s1_i = ft_strlen(s1) - 1;
	s2_i = ft_strlen(s2) - 1;
	count = 0;
	if (n == 0)
		return (0);
	while (s1[s1_i] && s2[s2_i] && s1[s1_i] == s2[s2_i] && count < n - 1
		&& s1_i != 0 && s2_i != 0)
	{
		s1_i--;
		s2_i--;
		count++;
	}
	return ((unsigned char)s1[s1_i] - (unsigned char)s2[s2_i]);
}
