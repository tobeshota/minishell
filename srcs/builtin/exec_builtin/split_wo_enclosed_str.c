/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_wo_enclosed_str.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 21:10:43 by toshota           #+#    #+#             */
/*   Updated: 2023/12/15 23:02:54 by toshota          ###   ########.fr       */
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
static void	nodeadd_upto_blank(t_env **node_cmd, char *str, int i)
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

/* nodeに囲い文字までの文字列を格納する（ほんとうは「今指しているポインタ〜次の囲い文字まで」の文字列を格納したい） */
static void	nodeadd_upto_encloser(t_env **node_cmd, char *str, char encloser)
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
		if (str[i] == splitter)
		{
			nodeadd_upto_blank(&node_cmd, str, i);
			str += ft_strlen(ft_nodelast(node_cmd)->content) + SPLITTER;
			i = -1;
		}
		else if (str[i] == '\'' || str[i] == '\"')
		{
			encloser = str[i];
			nodeadd_upto_encloser(&node_cmd, str, encloser);
			str += ft_strlen(ft_nodelast(node_cmd)->content)
				+ BEGINNING_OF_ENCLOSER + END_OF_ENCLOSER;
			i = -1;
		}
		i++;
	}
	cmd = node_to_array(node_cmd);
	return (ft_nodeclear(&node_cmd), cmd);
}
