/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 16:43:07 by toshota           #+#    #+#             */
/*   Updated: 2023/12/18 11:49:42 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

bool	is_specified_wildcard(char *str)
{
	if (ft_strchr(str, '*') == NULL) /* strの中にアスタリスクがなければfalse */
		return (false);
	if (is_file_exist(str) == true)
	/* strがファイルであればstr内にあるアスタリスクはファイル名またはディレクトリ名の一部 */
		return (false);
	return (true);
}

char	*double_to_sigle(char **array, char splitter)
{
	char	*str;
	char	splitter_str[2];
	char	*tmp;
	int		i;

	str = NULL;
	splitter_str[0] = splitter;
	splitter_str[1] = '\0';
	i = 0;
	while (array[i])
	{
		tmp = str;
		str = check_malloc(ft_strjoin(str, array[i]));
		free(tmp);
		if (array[i + 1])
		{
			tmp = str;
			str = check_malloc(ft_strjoin(str, splitter_str));
			free(tmp);
		}
		i++;
	}
	return (str);
}

/* ワイルドカードを展開する！

wildcard (*)
current working directory の directory-name,
	file-name の中から pattern matching するものを ascii 順に sort して出力
sort 順はロケールの設定の違いによるもので、42VM の ubuntu の bash に合わせてはいない。ascii順。
* は 0 byte 以上の任意の文字に置き換わる
通常 : 隠しファイル以外が検索対象
.* : 隠しファイルのみ検索対象

*/

/*
cwd　[/Users/tobeshota/workspace/42/minishell/srcs/pipex]
引数　[is*]
出力　[is_cmd.c is_file_ok.c is_specified_control_operators.c is_specified_file.c is_utils.c]
 */
bool	check_opendir(DIR *dir, char *path)
{
	if (dir == NULL)
		return put_error_w_file(path, strerror(errno)), false;
	return true;
}

bool	check_closedir(int ret)
{
	if (ret == -1)
		return ft_putendl_fd(strerror(errno), STDERR_FILENO), false;
	return true;
}

void	ft_nodeswap(t_env *n1, t_env *n2)
{
	char *tmp_content;
	int tmp_order;

	tmp_content = n1->content;
	n1->content = n2->content;
	n2->content = tmp_content;

	tmp_order = n1->order;
	n1->order = n2->order;
	n2->order = tmp_order;
}

/* オーダーに沿って昇順にソートする */
void	ft_nodesort(t_env **node)
{
	t_env	*head;

	while (true)
	{
		head = *node;
		while (true)
		{
			if (head->next == NULL)
				break ;
			else if (head->order > head->next->order)
				ft_nodeswap(head, head->next);	/* 要素だけ変える */
			head = head->next;
		}
		if ((*node)->next == NULL)
			break ;
		*node = (*node)->next;
	}
	ft_nodefirst(node);
}

/* ワイルドカードを展開しexpandedに入れる */
void	get_wild(t_env **expanded)
{
	char			cwd[PATH_MAX];
	DIR				*dir;
	struct	dirent	*entry;

	if (getcwd(cwd, PATH_MAX) == NULL)
		return ;
	dir = opendir(cwd);
	if (check_opendir(dir, cwd) == false)
		return ;
	entry = readdir(dir);
	while (entry)
	{
		if (*expanded == NULL)
			*expanded = ft_nodenew(entry->d_name);
		else
			ft_nodeadd_back(expanded, ft_nodenew(entry->d_name));
		entry = readdir(dir);
	}
	check_closedir(closedir(dir));
	get_order(*expanded);
	ft_nodesort(expanded);
	// put_node_for_debug(*expanded);
}

void	expand_argv_param_w_wildcard(t_env *node)
{
	char	*prefix;	/* 前方一致文字 */
	char	*backward;	/* 後方一致文字 */
	t_env	*expanded;

	prefix = check_malloc(ft_substr(node->content, 0, strlen_until_c(node->content, '*')));    /* 前方一致文字を取得する */
	backward = check_malloc(ft_strdup(ft_strrchr(node->content, '*') + 1));/* 後方一致文字を取得する */
	expanded = NULL;
// ft_printf("{%s}{%s}\n", prefix, backward);

	/* ワイルドカードを展開しexpandedに入れる */
	get_wild(&expanded);
	/* expandedをascii順に昇順ソートする */
	/* expandedの各contentのうち，prefixとbackwardのマッチ条件に該当しないものを削除する */
	/* expandedの各contentを二重配列にする */
	/* 二重配列をスペース区切りの一重配列にする */
	/* node->contentに一重配列を代入する */
	return free(prefix), free(backward), ft_nodeclear(&expanded);
}

/*
cwd　[/Users/tobeshota/workspace/42/minishell/srcs/pipex]
引数　[echo -n is* get*]
出力　[echo -n is_cmd.c is_file_ok.c is_specified_control_operators.c is_specified_file.c is_utils.c get_child.c get_cmd_absolute_path.c get_cmd_absolute_path_utils.c get_cmd_arg_fd.c get_cmd_count.c get_fd.c get_loop_pipex.c get_pipe.c get_pipex.c get_splitted_argv.c get_splitter.c]
 */
void	expand_argv_w_wildcard(char **argv_to_be_updated)
{
	char	**array;
	t_env	*node;
	char	*tmp;

	array = split_wo_enclosed_str(*argv_to_be_updated, ' ');
	node = array_to_node(array); /* argv_to_be_updatedを分割しリストに格納する（∵文字列操作をしやすくするため！） */
	all_free_tab(array);
	while (true) /* whileで回して各ノードごとに変数展開する */
	{
		if (is_specified_wildcard(node->content))
			expand_argv_param_w_wildcard(node); /* wildcardを含む引数を展開する */
		if (node->next == NULL)
			break ;
		node = node->next;
	}
	ft_nodefirst(&node);
	tmp = *argv_to_be_updated;
	array = node_to_array(node);
	*argv_to_be_updated = double_to_sigle(array, ' '); /* リストを二重配列に戻し，二重配列をスペース区切りの一重配列にする */
	return (all_free_tab(array), free(tmp), ft_nodeclear(&node));
}

void	expand_wildcard(char **h_argv) /* 引数としてヒープ領域で確保された文字列を取る */
{
	int arg_i;

	arg_i = 0;
	while (h_argv[arg_i]) /* whileで回して各文字列ごとに変数展開する */
	{
		if (is_specified_wildcard(h_argv[arg_i]))
			expand_argv_w_wildcard(&h_argv[arg_i]); /* argv[arg_i]内のwildcardを変数展開しargv[arg_i]の値を更新する */
		arg_i++;
	}
}
