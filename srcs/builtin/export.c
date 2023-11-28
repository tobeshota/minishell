/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:39:21 by toshota           #+#    #+#             */
/*   Updated: 2023/11/28 15:26:07 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

// 文字列にイコールがない場合セグフォするのを防ぐ！
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

static char *get_envp_content_for_export(char *content)
{
	char *env_content;

	env_content = check_malloc(ft_strjoin("declare -x ", content));
	if (ft_strchr(env_content, '='))
		enclose_env_content_in_double_quotes(&env_content);
	return env_content;
}

static void put_envp_content_for_export(char *content, t_pipex *pipex)
{
	char *env_content;

	env_content = get_envp_content_for_export(content);
	ft_putendl_fd(env_content, pipex->outfile_fd);
	free(env_content);
}

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

void	ft_sort_int_tab(int *tab, int size)
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

int *get_env_order(t_env *node)
{
	int i;
	int *env_order;

	i = 0;
	env_order = (int *)check_malloc(malloc(sizeof(int) * ft_nodesize(node)));
	while (node->next)
	{
		env_order[i++] = node->order;
		ft_nodenext(&node);
	}
	env_order[i] = node->order;
	ft_nodefirst(&node);
	// for(int i = 0; env_order[i]; i++)
	// 	ft_printf(">>> %d\n", env_order[i]);
	return env_order;
}

static void add_new_value(char **cmd, t_env **env)
{
	int max_order;

	max_order = ft_nodesize(*env);
	*env = ft_nodelast(*env);
	ft_nodeadd_back(env, check_malloc(ft_nodenew(cmd[1])));
	ft_nodenext(env);
	(*env)->order = max_order + 1;
}

static bool is_additional_value_new(char *added_value, t_env *env)
{
	char *added_varname;
	char *env_varname;

	added_varname = check_malloc(ft_substr(added_value, 0, ft_strchr(added_value, '=') - added_value));
	while(env->next)
	{
		env_varname = (char *)check_malloc(malloc(sizeof(char) * (strlen_until_c(env->content, '=') + 1)));
		ft_strlcpy(env_varname, env->content, strlen_until_c(env->content, '=') + 1);
		ft_printf("[%s]\t[%s]\n", added_varname, env_varname);
		if(is_match(added_value, env_varname))
			return free(added_varname), free(env_varname), ft_nodefirst(&env), false;
		ft_nodenext(&env);
		free(env_varname);
	}
	env_varname = (char *)check_malloc(malloc(sizeof(char) * (strlen_until_c(env->content, '=') + 1)));
	ft_strlcpy(env_varname, env->content, strlen_until_c(env->content, '=') + 1);
	ft_printf("[%s]\t[%s]\n", added_varname, env_varname);
	if(is_match(added_value, env_varname))
		return free(added_varname), free(env_varname), ft_nodefirst(&env), false;
	return free(added_varname), free(env_varname), ft_nodefirst(&env), true;
}

int	exec_export(char **cmd, t_env **env, t_pipex *pipex)
{
	int order;
	int max_order;
	int *env_order;
	int i;

	max_order = ft_nodesize(*env);
	ft_printf("━━━▶︎max_order:\t%d\n", max_order);
	if(cmd[1])	/* いまから追加しようとしている環境変数の名前varnameが既存のものと同じ場合，その定義を更新する！ */
	{
		// 追加変数は新規か
		if (is_additional_value_new(cmd[1], *env) == true)
		{
			add_new_value(cmd, env);
		}
		// else
		// {

		// }




	}
	else
	{
		/* 引数が指定されていない場合，環境変数を一覧表示する */
		env_order = get_env_order(*env);
		ft_sort_int_tab(env_order, ft_nodesize(*env));
		i = 1;
		while(i < ft_nodesize(*env))
		{
			while(env_order[i] != (*env)->order)
				ft_nodenext(env);
			put_envp_content_for_export((*env)->content, pipex);
			ft_nodefirst(env);
			i++;
		}
		free(env_order);
	}
	return (ft_nodefirst(env), true);
}
