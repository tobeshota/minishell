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

#define ENCLOSER 1
/* nodeに空白までの文字列を格納する */
void nodeadd_upto_blank(t_env **node_cmd, char *str, int i)
{
	t_env	*new;
	char	*content;
	char	*content_wo_quotas;

	content = check_malloc(ft_substr(str, 0, i));
	content_wo_quotas = omit_str(content, "\'\"");
	new = ft_nodenew(content_wo_quotas);
	free(content);
	free(content_wo_quotas);
	if (*node_cmd == NULL)
		*node_cmd = new;
	else
		ft_nodeadd_back(node_cmd, new);
}

/* nodeに囲い文字までの文字列を格納する（ほんとうは「今指しているポインタ〜次の囲い文字まで」の文字列を格納したい） */
void nodeadd_upto_encloser(t_env **node_cmd, char *str, char encloser)
{
	t_env	*new;
	int		len_upto_next_encloser;
	char	*content;
	char	*content_wo_quotas;

	// len_upto_next_encloser = strlen_until_c(str + ENCLOSER, encloser);
	len_upto_next_encloser = ft_strchr(ft_strchr(str, encloser) + ENCLOSER, encloser) - str;
	content = check_malloc(ft_substr(str, 0, len_upto_next_encloser + ENCLOSER));

	content_wo_quotas = omit_str(content, "\'\"");
	new = ft_nodenew(content_wo_quotas);
	free(content);
	free(content_wo_quotas);
	if (*node_cmd == NULL)
		*node_cmd = new;
	else
		ft_nodeadd_back(node_cmd, new);
}
/*
export c=abc" def"
export a=abc "b=def ghi"
*/
char **ft_split_x(char *str, char splitter)
{
	t_env *node_cmd;
	char **cmd;
	char encloser;
	int i;

	i = 0;
	node_cmd = NULL;
	if (ft_strchr(str, '\'') == NULL && ft_strchr(str, '\"') == NULL)
		return check_malloc(ft_split(str, splitter));
	while (str[i])
	{
		if (str[i] == ' ')
		{
			// nodeに空白までの文字列を格納する
			nodeadd_upto_blank(&node_cmd, str, i);
			str += i + 1;
			i = -1;
		}
		else if (str[i] == '\'' || str[i] == '\"')
		{
			encloser = str[i];
			// nodeに囲い文字までの文字列を格納する（ほんとうは「今指しているポインタ〜次の囲い文字まで」の文字列を格納したい）
			nodeadd_upto_encloser(&node_cmd, str, encloser);
			str += ENCLOSER;
			str += i + strlen_until_c(str, encloser) + 1;
			i = -1;
		}
		i++;
	}
	cmd = node_to_array(node_cmd);
	return ft_nodeclear(&node_cmd), cmd;
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
	// cmd = check_malloc(split_wo_enclosed_str(pipex->cmd_absolute_path_with_parameter[cmd_i], ' '));
	cmd = check_malloc(ft_split_x(pipex->cmd_absolute_path_with_parameter[cmd_i], ' '));
put_array_for_debug(cmd);
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
