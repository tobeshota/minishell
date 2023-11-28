/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:39:21 by toshota           #+#    #+#             */
/*   Updated: 2023/11/28 20:36:50 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#define OLD_ENV_TO_BE_UPDATED_IS_NOTING NULL

// 文字列にイコールがない場合セグフォするのを防ぐ！
static void enclose_env_content_in_double_quotes(char **env_content)
{
	char *identifier_with_equal;
	char *identifier_definition;
	char *tmp;

	identifier_with_equal = check_malloc(ft_substr(*env_content, 0, ft_strchr(*env_content, '=') - *env_content + 1));
	identifier_definition = check_malloc(ft_strdup(ft_strchr(*env_content, '=') + 1));

	tmp = identifier_definition;
	identifier_definition = check_malloc(ft_strjoin("\"", identifier_definition));
	free(tmp);

	tmp = identifier_definition;
	identifier_definition = check_malloc(ft_strjoin(identifier_definition, "\""));
	free(tmp);

	tmp = *env_content;
	*env_content = check_malloc(ft_strjoin(identifier_with_equal, identifier_definition));
	free(tmp);
	free(identifier_with_equal);
	free(identifier_definition);
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
	return env_order;
}

static bool is_append_properly_written(char current_c, char next_c)
{
	if (current_c == '+')
	{
		if (next_c == '=')
			return true;
		return false;
	}
	return true;
}

// プラス記号は次にイコールがある時のみ容認する
static bool check_identifier(char *identifier)
{
	int i;

	i = 0;
	if (ft_isalpha(identifier[i]) == false && identifier[i] != '_')
	{
		ft_putstr_fd("bash: export: '", STDERR_FILENO);
		ft_putstr_fd(identifier, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		return false;
	}
	while (identifier[i])
	{
		if (ft_isalnum(identifier[i]) == false && identifier[i] != '_' && is_append_properly_written(identifier[i], identifier[i+1]) == false)
		{
			ft_putstr_fd("bash: export: '", STDERR_FILENO);
			ft_putstr_fd(identifier, STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			return false;
		}
		i++;
	}
	return true;
}

static void add_new_value(char *added_value, t_env **env)
{
	int max_order;

	if (check_identifier(added_value) == false)
		return;
	max_order = ft_nodesize(*env);
	*env = ft_nodelast(*env);
	ft_nodeadd_back(env, check_malloc(ft_nodenew(added_value)));
	ft_nodenext(env);
	(*env)->order = max_order + 1;
}

// 追記を対応する！
static t_env *get_old_env_to_be_updated(char *added_value, t_env *env)
{
	char *added_identifier;
	char *env_identifier;
	t_env *old_env_to_be_updated;

	if (ft_strnstr(added_value, "+=", ft_strlen(added_value)))
		added_identifier = check_malloc(ft_substr(added_value, 0, ft_strchr(added_value, '+') - added_value));
	else
		added_identifier = check_malloc(ft_substr(added_value, 0, ft_strchr(added_value, '=') - added_value));
	while(true)
	{
		env_identifier = (char *)check_malloc(malloc(sizeof(char) * (strlen_until_c(env->content, '=') + 1)));
		ft_strlcpy(env_identifier, env->content, strlen_until_c(env->content, '=') + 1);
		if(is_match(added_identifier, env_identifier))
		{
			old_env_to_be_updated = env;
			return free(added_identifier), free(env_identifier), ft_nodefirst(&env), old_env_to_be_updated;
		}
		if (env->next == NULL)
			break;
		ft_nodenext(&env);
		free(env_identifier);
	}
	return free(added_identifier), free(env_identifier), ft_nodefirst(&env), OLD_ENV_TO_BE_UPDATED_IS_NOTING;
}

static void update_value(char *added_value, t_env **env)
{
	t_env *old_env_to_be_updated;
	char *added_identifier;
	char *tmp;

	old_env_to_be_updated = get_old_env_to_be_updated(added_value, *env);
	if (ft_strnstr(added_value, "+=", ft_strlen(added_value)))
	{
		if (ft_strchr(old_env_to_be_updated->content, '='))
			added_identifier = check_malloc(ft_substr(added_value, 0, ft_strchr(added_value, '+') - added_value));
		else
			added_identifier = check_malloc(ft_substr(added_value, 0, ft_strchr(added_value, '+') - added_value - ft_strlen("=")));
		tmp = old_env_to_be_updated->content;
		old_env_to_be_updated->content = check_malloc(ft_strjoin(old_env_to_be_updated->content, added_value + (ft_strlen(added_identifier) + ft_strlen("+="))));
		free(added_identifier);
	}
	else
	{
		tmp = old_env_to_be_updated->content;
		old_env_to_be_updated->content = check_malloc(ft_strdup(added_value));
	}
	free(tmp);
}

/* 引数が指定されていない場合，環境変数を一覧表示する */
static void show_env(t_env **env, t_pipex *pipex)
{
	int i;
	int *env_order;

	i = 1;
	env_order = get_env_order(*env);
	ft_sort_int_tab(env_order, ft_nodesize(*env));
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

/* ファイル分割などを行なってnorminetteに対応する！ */
int	exec_export(char **cmd, t_env **env, t_pipex *pipex)
{
	int *env_order;
	int i;

	i = 1;
	if(cmd[i])
	{
		while(cmd[i])
		{
			if (get_old_env_to_be_updated(cmd[i], *env) == OLD_ENV_TO_BE_UPDATED_IS_NOTING)
				add_new_value(cmd[i], env);
			else
				update_value(cmd[i], env);
			ft_nodefirst(env);
			i++;
		}
	}
	else
		show_env(env, pipex);
	return (ft_nodefirst(env), true);
}
