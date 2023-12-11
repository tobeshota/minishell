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
	return (is_match(cmd, "_") \
	|| (ft_strlen(cmd) >= 2 && !ft_strncmp(cmd, "_=", 2)));
}

bool	is_match(char *s1, char *s2)
{
	return (s1 && s2 && ft_strlen(s1) == ft_strlen(s2) \
	&& (!ft_strncmp(s1, s2, ft_strlen(s1))));
}

bool	is_cmd_builtin(char *cmd)
{
	return (is_match(cmd, "echo") || is_match(cmd, "/bin/echo")
		|| is_match(cmd, "cd") || is_match(cmd, "/usr/bin/cd")
		|| is_match(cmd, "pwd") || is_match(cmd, "/bin/pwd")
		|| is_match(cmd, "export") || is_match(cmd, "unset")
		|| is_match(cmd, "env") || is_match(cmd, "/usr/bin/env")
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
// 			// 	break;
// 			// 囲い文字が来たときインクリメントを終了する
// 			if (str[str_i][c_i] == encloser)
// 				return len;
// 			len++;
// 			c_i++;
// 		}
// 		str_i++;
// 		c_i = 0;
// 	}
// 	return -1;
// }

// 囲い文字の初めから終わりまでの文字列をresultに入れる
// char *strdup_between_encloser(char **str, int *str_i, int *c_i, char encloser)
// {
// 	char *dest;
// 	int dest_i;

// 	if (strlen_between_encloser(str, *str_i, *c_i, encloser) == -1)
// 		return NULL;
// 	dest = (char *)check_malloc(malloc(sizeof(char) * (strlen_between_encloser(str, *str_i, *c_i, encloser) + 1)));
// 	// 各strを見る
// 	dest_i = 0;
// 	while(str[*str_i])
// 	{
// 		// 各strの各文字を見る
// 		while(str[*str_i][*c_i])
// 		{
// 			// (*c_i)++;
// 			// if (str[*str_i][*c_i] == '\0')
// 			// 	break;
// 			// 囲い文字が来たときコピーを終了する
// 			if(str[*str_i][*c_i] == encloser)
// 			{
// 				dest[dest_i] = '\0';
// 				return dest;
// 			}
// 			dest[dest_i] = str[*str_i][*c_i];
// 			dest_i++;
// 			(*c_i)++;
// 		}
// 		(*str_i)++;
// 		*c_i = 0;
// 	}
// 	dest[dest_i] = '\0';
// 	return dest;
// }

// 囲い文字で囲われている文字列を連結する
// char **strjoin_enclosed_by_c(char **str, char encloser)
// {
// 	char **result;
// 	int len_between_encloser;
// 	int str_i;
// 	int c_i;

// 	result = (char **)check_malloc(malloc(sizeof(char *) * (get_element_count(str) + 1)));
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
// 					return NULL;
// 				result[str_i] = (char *)check_malloc(malloc(sizeof(char) * (strlen_between_encloser(str, str_i, c_i, encloser) + 1)));
// 				result[str_i] = check_malloc(strdup_between_encloser(str, &str_i, &c_i, encloser));
// 				if(str[str_i])
// 					break ;
// 				continue ;
// 			}
// 		}
// 		result[str_i] = check_malloc(ft_strdup(str[str_i]));
// 	}
// 	result[str_i] = NULL;
// 	return result;
// }

char	**split_wo_enclosed_str(char const *str, char splitter, char *encloser)
{
	char **str_splitted_by_encloser;

	str_splitted_by_encloser = check_malloc(ft_split(str, splitter));
/* 囲い文字のある文，囲い文字のない文を二重配列arrayにコピーする */
// '\0' が来るまで繰り返す
// {
	// 囲い文字 ∨ '\0' が来るまでの文字列strの長さを取得する(strlen_until_c)
	// 囲い文字 ∨ '\0' が来るまでの文字列strの長さぶんmallocする(malloc)
	// 囲い文字 ∨ '\0' が来るまでの文字列strの長さぶんコピーする(ft_strlcpy)
	// 囲い文字が来るまでstrをインクリメントする(+=strlen_until_c)
	// array[i]のiをインクリメントする
// }

/* arrayの各文字列のうち，囲い文字のない文字列はft_splitによって分割する．他方で，囲い文字のある文字列はft_strdupする．そしてft_split，ft_strdupの返り値のアドレスを，NULLとなるまでi++したchar *result[i]に格納する． */

}

int	exec_builtin(t_env **env, t_pipex *pipex, int cmd_i)
{
	int		ret;
	char	**cmd;
	char	**cmd_enclosed_by_quotas;
	char	*target;

	ret = false;
	target = pipex->cmd_absolute_path[cmd_i];
	/* export A=" abc" のとき cmd[1]=A=" abc"となるようにする！
	入力	export A=" abc"
	現在	"A= "   "abc"
	理想	"A= abc"
	*/
	if(ft_strchr(pipex->cmd_absolute_path_with_parameter[cmd_i], '\'') == NULL && ft_strchr(pipex->cmd_absolute_path_with_parameter[cmd_i], '\"'))
		cmd = check_malloc(ft_split(pipex->cmd_absolute_path_with_parameter[cmd_i], ' '));
	else
		cmd = (check_malloc(split_wo_enclosed_str(pipex->cmd_absolute_path_with_parameter[cmd_i], ' ', "\'\"")));
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
	return (all_free_tab(cmd), all_free_tab(cmd_enclosed_by_quotas), ret);
}
