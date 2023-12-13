/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:01:50 by toshota           #+#    #+#             */
/*   Updated: 2023/11/21 12:00:11 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

bool	is_under_bar(char *cmd)
{
	return (is_match(cmd, "_") || (ft_strlen(cmd) >= 2 && !ft_strncmp(cmd, "_=",
				2)));
}

bool	is_match(char *s1, char *s2)
{
	return (s1 && s2 && ft_strlen(s1) == ft_strlen(s2) && (!ft_strncmp(s1, s2,
				ft_strlen(s1))));
}

bool	is_cmd_builtin(char *cmd)
{
	return (is_match(cmd, "echo") || is_match(cmd, "/bin/echo") || is_match(cmd,
			"cd") || is_match(cmd, "/usr/bin/cd") || is_match(cmd, "pwd")
		|| is_match(cmd, "/bin/pwd") || is_match(cmd, "export") || is_match(cmd,
			"unset") || is_match(cmd, "env") || is_match(cmd, "/usr/bin/env")
		|| is_match(cmd, "exit"));
}

// 次に囲い文字が来るまでの文字の長さを取得する
// int strlen_between_encloser(char **str, int str_i, int c_i, char encloser)
// {
// 	int len;

// 	len = 0;
// 	// 各strを見る
// 	while(str[str_i])
// 	{
// 		// 各strの各文字を見る
// 		while(str[str_i][c_i])
// 		{
// 			// c_i++;
// 			// if (str[str_i][c_i] == '\0')
// 			// 	break ;
// 			// 囲い文字が来たときインクリメントを終了する
// 			if (str[str_i][c_i] == encloser)
// 				return (len);
// 			len++;
// 			c_i++;
// 		}
// 		str_i++;
// 		c_i = 0;
// 	}
// 	return (-1);
// }

// 囲い文字の初めから終わりまでの文字列をresultに入れる
// char *strdup_between_encloser(char **str, int *str_i, int *c_i,
		// char encloser)
// {
// 	char *dest;
// 	int dest_i;

// 	if (strlen_between_encloser(str, *str_i, *c_i, encloser) == -1)
// 		return (NULL);
// 	dest = (char *)check_malloc(malloc(sizeof(char)
				// * (strlen_between_encloser(str, *str_i, *c_i, encloser) + 1)));
// 	// 各strを見る
// 	dest_i = 0;
// 	while(str[*str_i])
// 	{
// 		// 各strの各文字を見る
// 		while(str[*str_i][*c_i])
// 		{
// 			// (*c_i)++;
// 			// if (str[*str_i][*c_i] == '\0')
// 			// 	break ;
// 			// 囲い文字が来たときコピーを終了する
// 			if(str[*str_i][*c_i] == encloser)
// 			{
// 				dest[dest_i] = '\0';
// 				return (dest);
// 			}
// 			dest[dest_i] = str[*str_i][*c_i];
// 			dest_i++;
// 			(*c_i)++;
// 		}
// 		(*str_i)++;
// 		*c_i = 0;
// 	}
// 	dest[dest_i] = '\0';
// 	return (dest);
// }

// 囲い文字で囲われている文字列を連結する
// char **strjoin_enclosed_by_c(char **str, char encloser)
// {
// 	char **result;
// 	int len_between_encloser;
// 	int str_i;
// 	int c_i;

// 	result = (char **)check_malloc(malloc(sizeof(char *)
				// * (get_element_count(str) + 1)));
// 	str_i = -1;
// 	// 各strを見る
// 	while(str[++str_i])
// 	{
// 		c_i = -1;
// 		// 各strの各文字を見る
// 		while(str[str_i][++c_i])
// 		{
// 			// 囲い文字が来たとき
// 			if (str[str_i][c_i] == encloser)
// 			{
// 				c_i++;
// 				if (strlen_between_encloser(str, str_i, c_i, encloser) == -1)
// 					return (NULL);
// 				result[str_i] = (char *)check_malloc(malloc(sizeof(char)
							// * (strlen_between_encloser(str, str_i, c_i,
							// 		encloser) + 1)));
// 				result[str_i] = check_malloc(strdup_between_encloser(str,
							// &str_i, &c_i, encloser));
// 				if(str[str_i])
// 					break ;
// 				continue ;
// 			}
// 		}
// 		result[str_i] = check_malloc(ft_strdup(str[str_i]));
// 	}
// 	result[str_i] = NULL;
// 	return (result);
// }

void ft_nodedel_front(t_env **cmd_node)
{
	t_env *unseted_node;

	if (is_node_first(*cmd_node))
		return ;
	else
	{
		unseted_node = (*cmd_node)->prev;
		if (is_node_first(unseted_node) == false)
		{
			unseted_node->prev->next = unseted_node->next;
			unseted_node->next->prev = unseted_node->prev;
		}
		ft_nodedelone(&unseted_node);
	}
}

char	*ft_str_c_join(char const *s1, char const c)
{
	char	s2[2];

	s2[0] = c;
	s2[1] = '\0';
	return ft_strjoin(s1, s2);
}

/* 次に同じ囲い文字が現れるまで文字列をcmd_node->contentに文字列を追加する */
void append_until_next_same_encloser_appears(t_env **cmd_node, int content_i, char splitter)
{
	char	encloser;
	char	*enclosed_content;
	char	*tmp;

	// char encloserに囲い文字を取得する（次にまたその囲い文字が来るまでコピーを繰り返す）
	encloser = (*cmd_node)->content[content_i];
	// char *enclosed_contentにcmd_node->content[0 ~ iまでの文字]をヒープ領域で格納する
	enclosed_content = check_malloc(malloc(sizeof(char) * (strlen_until_c((*cmd_node)->content, encloser) + 1)));
	ft_strlcpy(enclosed_content, (*cmd_node)->content, (strlen_until_c((*cmd_node)->content, encloser) + 1));
	// i++; して囲い文字の次の文字を参照するようにする
	content_i++;
	// cmd_node->nextがあるまで繰り返す．
	while ((*cmd_node)->next)
	{
		// cmd_node->content[i]があるまで繰り返す
		while ((*cmd_node)->content[content_i])
		{
			// 次に同じ囲い文字が来たら
			if ((*cmd_node)->content[content_i] == encloser)
			{
				// 囲い文字以降に文字が存在するなら
				// if ((*cmd_node)->next)
				if ((*cmd_node)->content[content_i + 1])
				{
					// 次に区切り文字が来るまでの文字列（==次のノードのcontentすべて）をft_strjoinで連結する
					tmp = enclosed_content;
					enclosed_content = check_malloc(ft_strjoin(enclosed_content, (*cmd_node)->content + 1));
					free(tmp);
				}
				free((*cmd_node)->content);
				(*cmd_node)->content = check_malloc(ft_strdup(enclosed_content));

				free(enclosed_content);
				ft_nodefirst(cmd_node);
				return ;
			}
			// ft_strjoin(enclosed_content, &cmd_node->content[i])を入れる
			tmp = enclosed_content;
			enclosed_content = check_malloc(ft_str_c_join(enclosed_content, (*cmd_node)->content[content_i]));
			free(tmp);
			// iをインクリメントする
			content_i++;
		}
		// ft_splitにより消されてしまった囲い文字内の区切り文字を追加する
		tmp = enclosed_content;
		enclosed_content = check_malloc(ft_str_c_join(enclosed_content, splitter));
		free(tmp);
		// 次のノードへ．
		ft_nodenext(cmd_node);
		// 前回のノードを削除する
		ft_nodedel_front(cmd_node);
		// iを0にしcontentの先頭を指し示すようにする
		content_i = 0;
	}

	// cmd_node->content[i]があるまで繰り返す
	while ((*cmd_node)->content[content_i])
	{
		// 次に同じ囲い文字が来たら
		if ((*cmd_node)->content[content_i] == encloser)
		{
			// 囲い文字以降に文字が存在するなら
			// if ((*cmd_node)->next)
			if ((*cmd_node)->content[content_i + 1])
			{
				// 次に区切り文字が来るまでの文字列（==次のノードのcontentすべて）をft_strjoinで連結する
				tmp = enclosed_content;
				enclosed_content = check_malloc(ft_strjoin(enclosed_content, (*cmd_node)->content + 1));
				free(tmp);
			}
			free((*cmd_node)->content);
			(*cmd_node)->content = check_malloc(ft_strdup(enclosed_content));

			free(enclosed_content);
			ft_nodefirst(cmd_node);
			return ;
		}
		// ft_strjoin(enclosed_content, &cmd_node->content[i])を入れる
		tmp = enclosed_content;
		enclosed_content = check_malloc(ft_str_c_join(enclosed_content, (*cmd_node)->content[content_i]));
		free(tmp);
		// iをインクリメントする
		content_i++;
	}
	// ノードを最初にする
	ft_nodefirst(cmd_node);
}
char	**split_wo_enclosed_str(char const *str, char splitter)
{
	t_env	*cmd_node;
	char	**cmd;
	char	encloser;
	char	*enclosed_content;
	int		content_i;

	cmd = check_malloc(ft_split(str, splitter));
	// 囲い文字（\'\"）がなかったら
	if (ft_strchr(str, '\'') == NULL && ft_strchr(str, '\"') == NULL)
		// splitしたものを返す
		return cmd;
// return cmd;
	// 文字列をリストに格納する
	cmd_node = array_to_node(cmd);
put_node_for_debug(cmd_node);
	// cmd_node->nextがあるまで繰り返す．
	while (cmd_node->next)
	{
		content_i = 0;
		// cmd_node->content[i]があるまで繰り返す
		while (cmd_node->content[content_i])
		{
			// もしcmd_node->content[i]が囲い文字であれば，
			if (cmd_node->content[content_i] == '\'' || cmd_node->content[content_i] == '\"')
				/* 次に同じ囲い文字が現れるまで文字列をcmd_node->contentに文字列を追加する */
				append_until_next_same_encloser_appears(&cmd_node, content_i, splitter);
			// iをインクリメントする
			content_i++;
		}
		ft_nodenext(&cmd_node);
	}
	// リストを文字列に格納する
	ft_nodefirst(&cmd_node);
	all_free_tab(cmd);
	cmd = node_to_array(cmd_node);
	return ft_nodeclear(&cmd_node), cmd;
}

int	exec_builtin(t_env **env, t_pipex *pipex, int cmd_i)
{
	int		ret;
	char	**cmd;
	char	*target;

	ret = false;
	target = pipex->cmd_absolute_path[cmd_i];
	/* export A=" abc" のとき cmd[1]=A=" abc"となるようにする！
	入力	export A=" abc"
	現在	"A= "   "abc"
	理想	"A= abc"
	*/
	cmd = check_malloc \
	(split_wo_enclosed_str(pipex->cmd_absolute_path_with_parameter[cmd_i], ' '));
	if (is_match(target, "/bin/echo") || is_match(target, "echo"))
		ret = exec_echo(cmd, pipex);
	else if (is_match(target, "/usr/bin/cd") || is_match(target, "cd"))
		ret = exec_cd(cmd, env, pipex);
	else if (is_match(target, "/bin/pwd") || is_match(target, "pwd"))
		ret = exec_pwd(pipex);
	else if (is_match(target, "export"))
		ret = exec_export(cmd, env, pipex);
	else if (is_match(target, "unset"))
		ret = exec_unset(cmd, env);
	else if (is_match(target, "/usr/bin/env") || is_match(target, "env"))
		ret = exec_env(env, pipex);
	else if (is_match(target, "exit"))
		ret = exec_exit(cmd, pipex);
	return (all_free_tab(cmd), ret);
}
