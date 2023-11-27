/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:39:21 by toshota           #+#    #+#             */
/*   Updated: 2023/11/27 16:48:50 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	get_order(t_env *node)
{
	t_env	*test;

	test = node;
	while (node->next)
	{
		node->order = 1;
		while (test->next)
		{
			if (ft_strncmp(node->content, test->content, ft_strlen(test->content)) > 0)
				node->order++;
			ft_nodenext(&test);
		}
		if (ft_strncmp(node->content, test->content, ft_strlen(test->content)) > 0)
			node->order++;
		ft_nodenext(&node);
		ft_nodefirst(&test);
	}
}

static void enclose_env_content_in_double_quotes(char **env_content)
{
	char *varname_with_equal;
	char *varname_definition;
	char *tmp;

	varname_with_equal = check_malloc(ft_substr(*env_content, 0, ft_strchr(*env_content, '=') - *env_content + 1));
	varname_definition = check_malloc(ft_strdup(ft_strchr(*env_content, '=') + 1));

	tmp = varname_definition;
	varname_definition = check_malloc(ft_strjoin("\"", varname_definition));
	free(tmp);

	tmp = varname_definition;
	varname_definition = check_malloc(ft_strjoin(varname_definition, "\""));
	free(tmp);

	tmp = *env_content;
	*env_content = check_malloc(ft_strjoin(varname_with_equal, varname_definition));
	free(tmp);
	free(varname_with_equal);
	free(varname_definition);
}

static char *get_envp_content_for_export(t_env *env)
{
	char *env_content;

	ft_printf("%5d\t", env->order);
	env_content = check_malloc(ft_strjoin("declare -x ", env->content));
	enclose_env_content_in_double_quotes(&env_content);
	return env_content;
}

static void put_envp_content_for_export(t_env *env, t_pipex *pipex)
{
	char *env_content;

	env_content = get_envp_content_for_export(env);
	ft_putendl_fd(env_content, pipex->outfile_fd);
	free(env_content);
}

int	exec_export(char **cmd, t_env **env, t_pipex *pipex)
{
	int order;
	int max_order;
	char *envp_enclosed_in_double_quotes;

	max_order = ft_nodesize(*env);
	if(cmd[1])
	{
		// 新たに環境変数を追加するときに，最後の位置にある環境変数nodeのorderが消えていないか？
		*env = ft_nodelast(*env);
		ft_nodeadd_back(env, check_malloc(ft_nodenew(cmd[1])));
		ft_nodenext(env);
		(*env)->order = max_order + 1;
		max_order++;
	}
	else
	{
		/* 引数が指定されていない場合，環境変数を一覧表示する */
		// 昇順に出力する
		order = 0;
		while (++order <= max_order)
		{
			while ((*env)->next && (*env)->order != order)
				ft_nodenext(env);
			if ((*env)->next == NULL)	//	aが来たら止まってしまう．
				break;
			put_envp_content_for_export(*env, pipex);
			ft_nodefirst(env);
		}
	}
	return (ft_nodefirst(env), true);
}
