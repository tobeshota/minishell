/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshimurahiro <yoshimurahiro@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 09:35:08 by yoshimurahi       #+#    #+#             */
/*   Updated: 2023/11/30 10:58:20 by yoshimurahi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/expander.h"

size_t	find_equal(char *str)//文字列内でイコール('=')の位置を検出
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i + 1);
		i++;
	}
	return (0);
}

size_t	find_dollar(char *str)//与えられた文字列の中に$があるかどうかを判定する関数。あったらその位置＋１を返す。
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (i + 1);
		i++;
	}
	return (0);
}

int	loop_if_dollar_sign(t_tools *tools, char *str, char **tmp, int j)//環境変数に対応する値を取得し、それを元の文字列に結合
{//＄ ＆＆ !’　’ && $の次が"出ない時にこの関数を呼び出す
	int		k;
	int		ret;
	char	*tmp2;
	char	*tmp3;

	k = 0;
	ret = 0;
	while (tools->envp[k])
	{
		if (ft_strncmp(str + j + 1, tools->envp[k],
				find_equal(tools->envp[k]) - 1) == 0
			&& after_dol_lenght(str, j) - j == (int)find_equal(tools->envp[k]))
		{
			tmp2 = ft_strdup(tools->envp[k] + find_equal(tools->envp[k]));//先頭ポインタをイコールの次に移動
			tmp3 = ft_strjoin(*tmp, tmp2);
			free(*tmp);
			*tmp = tmp3;
			free(tmp2);
			ret = find_equal(tools->envp[k]);
		}
		k++;
	}
	if (ret == 0)
		ret = after_dol_lenght(str, j) - j;
	return (ret);
}

int	question_mark(char **tmp)
{
	free(*tmp);
	// *tmp = ft_itoa(error_num(g_status));
	*tmp = ft_itoa(1);//仮ね！
	return (ft_strlen(*tmp) + 1);
}