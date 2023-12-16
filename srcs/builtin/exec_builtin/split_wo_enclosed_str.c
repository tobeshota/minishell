/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_wo_enclosed_str.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 21:10:43 by toshota           #+#    #+#             */
/*   Updated: 2023/12/16 17:24:25 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#define SPLITTER 1
#define ENCLOSER 1
#define BEGINNING_OF_ENCLOSER 1
#define END_OF_ENCLOSER 1

static bool	does_encloser_exist(char *str)
{
	return (ft_strchr(str, '\'') || ft_strchr(str, '\"'));
}

static char	*omit_encloser_in_bos_and_eos(char *str)
{
	char	*result;
	char	encloser;

	result = (char *)check_malloc(malloc(sizeof(char) * (ft_strlen(str) + 1)));
	if (does_encloser_exist(str) == false)
	{
		ft_strlcpy(result, str, (ft_strlen(str) + 1));
	}
	else
	{
		encloser = str[ft_strlen(str) - 1];
		ft_strlcpy(result, str, (ft_strchr(str, encloser) - str) + 1);
		ft_strlcpy(result + ft_strlen(result), \
		ft_strchr(str, encloser) + BEGINNING_OF_ENCLOSER, \
		ft_strlen(ft_strchr(str, encloser)) - END_OF_ENCLOSER);
	}
	return (result);
}

/* nodeに空白までの文字列を格納する */
static void	nodeadd_from_0_to_i(t_env **node_cmd, char *str, int i)
{
	t_env	*new;
	char	*content;
	char	*content_wo_quotas;

	content = check_malloc(ft_substr(str, 0, i));
	content_wo_quotas = omit_encloser_in_bos_and_eos(content);
	new = ft_nodenew(content_wo_quotas);
	free(content);
	free(content_wo_quotas);
	if (*node_cmd == NULL)
		*node_cmd = new;
	else
		ft_nodeadd_back(node_cmd, new);
}

/* nodeに今指しているポインタから次の囲い文字までの文字列を格納する */
static void	nodeadd_upto_next_encloser(t_env **node_cmd, char *str, char encloser)
{
	t_env	*new;
	int		len_upto_next_encloser;
	char	*content;
	char	*content_wo_quotas;

	len_upto_next_encloser = \
	ft_strchr(ft_strchr(str, encloser) + ENCLOSER, encloser) - str;
	content = check_malloc \
	(ft_substr(str, 0, len_upto_next_encloser + ENCLOSER));
	content_wo_quotas = omit_encloser_in_bos_and_eos(content);
	new = ft_nodenew(content_wo_quotas);
	free(content);
	free(content_wo_quotas);
	if (*node_cmd == NULL)
		*node_cmd = new;
	else
		ft_nodeadd_back(node_cmd, new);
}

/* コマンドが囲い文字で囲われているときに引数に1つなぜかスペースが含まれる問題をなんとかする！
問題：
コマンドが囲い文字で囲われているときに引数に1つなぜかスペースが含まれる！

例：
入力　"echo"   "a"
出力　" a"
理想　"a"

問題の所在：
split_wo_enclosed_str();

*/

static bool are_there_any_str_to_be_stored_in_node_left(char *str)
{
	return (str[0] != '\0');
}

char	**split_wo_enclosed_str(char *str, char splitter)
{
	t_env	*node_cmd;
	char	**cmd;
	char	encloser;
	int		i;

	i = 0;
	node_cmd = NULL;
	if (ft_strchr(str, '\'') == NULL && ft_strchr(str, '\"') == NULL)
		return (check_malloc(ft_split(str, splitter)));
	while (str[i])
	{
		/* もし空白だったら */
		if (str[i] == splitter)
		{
			/* nodeに空白までの文字列を格納する */
			nodeadd_from_0_to_i(&node_cmd, str, i);
			str += ft_strlen(ft_nodelast(node_cmd)->content) + SPLITTER;
			i = -1;
		}
		/* もし囲い文字だったら */
		else if (str[i] == '\'' || str[i] == '\"')
		{
			encloser = str[i];
			/* nodeに今指しているポインタから次の囲い文字までの文字列を格納する */
			nodeadd_upto_next_encloser(&node_cmd, str, encloser);
			str += ft_strlen(ft_nodelast(node_cmd)->content)
				+ BEGINNING_OF_ENCLOSER + END_OF_ENCLOSER;
			i = -1;
		}
		i++;
	}
	/* 現状では最後にクウォートがあることが前提となっている！
	それゆえ，最後にクウォートがない場合，その文字列を取れない！
	もしstrに文字列が残っている場合は，whileループを抜けたとき，nodeに終端文字までの文字列を格納する！ */
	if (are_there_any_str_to_be_stored_in_node_left(str))
		nodeadd_from_0_to_i(&node_cmd, str, i);
	cmd = node_to_array(node_cmd);
	return (ft_nodeclear(&node_cmd), cmd);
}
