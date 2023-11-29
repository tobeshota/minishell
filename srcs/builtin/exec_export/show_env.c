/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 23:03:30 by toshota           #+#    #+#             */
/*   Updated: 2023/11/29 13:16:54 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	enclose_env_content_in_double_quotes(char **env_content)
{
	char	*identifier_with_equal;
	char	*identifier_definition;
	char	*tmp;

	identifier_with_equal = check_malloc(ft_substr(*env_content, 0,
				ft_strchr(*env_content, '=') - *env_content + 1));
	identifier_definition = \
	check_malloc(ft_strdup(ft_strchr(*env_content, '=') + 1));
	tmp = identifier_definition;
	identifier_definition = \
	check_malloc(ft_strjoin("\"", identifier_definition));
	free(tmp);
	tmp = identifier_definition;
	identifier_definition = \
	check_malloc(ft_strjoin(identifier_definition, "\""));
	free(tmp);
	tmp = *env_content;
	*env_content = check_malloc(ft_strjoin(identifier_with_equal,
				identifier_definition));
	free(tmp);
	free(identifier_with_equal);
	free(identifier_definition);
}

static void	put_envp_content_for_export(char *content, t_pipex *pipex)
{
	char	*env_content;

	env_content = check_malloc(ft_strjoin("declare -x ", content));
	if (ft_strchr(env_content, '='))
		enclose_env_content_in_double_quotes(&env_content);
	ft_putendl_fd(env_content, pipex->outfile_fd);
	free(env_content);
}

static void	ft_sort_int_tab(int *tab, int size)
{
	int	tmp;
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (tab[i] > tab[j])
			{
				tmp = tab[i];
				tab[i] = tab[j];
				tab[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static int	*get_env_order(t_env *node)
{
	int	i;
	int	*env_order;

	i = 0;
	env_order = (int *)check_malloc(malloc(sizeof(int) * ft_nodesize(node)));
	while (node->next)
	{
		env_order[i++] = node->order;
		ft_nodenext(&node);
	}
	env_order[i] = node->order;
	ft_nodefirst(&node);
	return (env_order);
}

/* 引数が指定されていない場合，環境変数を一覧表示する */
void	show_env(t_env **env, t_pipex *pipex)
{
	int	i;
	int	*env_order;

	i = 0;
	env_order = get_env_order(*env);
	ft_sort_int_tab(env_order, ft_nodesize(*env));
	while (i < ft_nodesize(*env))
	{
		while (env_order[i] != (*env)->order)
			ft_nodenext(env);
		put_envp_content_for_export((*env)->content, pipex);
		ft_nodefirst(env);
		i++;
	}
	free(env_order);
}
