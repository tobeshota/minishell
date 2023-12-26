/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quotes_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshimurahiro <yoshimurahiro@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 17:27:15 by cjia              #+#    #+#             */
/*   Updated: 2023/12/26 19:20:09 by yoshimurahi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "minishell.h"

void	init_move_to_last(int *i, int *frags, int *opp_quote_frags)
{
	*i = 0;
	*frags = 0;
	*opp_quote_frags = 0;
}

// 文字列中のi番目の文字を付け加える
char	*add_ith_c(char *str, char add, int ith)
{
	char	add_str[2];
	char	*before;
	char	*before_w_add;
	char	*after;
	char	*ret;

	add_str[0] = add;
	add_str[1] = '\0';
	before = check_malloc(ft_substr(str, 0, ith));
	after = check_malloc(ft_substr(str, ith, ft_strlen(str)));
	before_w_add = check_malloc(ft_strjoin(before, add_str));
	ret = check_malloc(ft_strjoin(before_w_add, after));
	return (free(before), free(after), free(before_w_add), ret);
}

// 文字列中のi番目の文字を消す
char	*omit_ith_c(char *str, int ith)
{
	char	*before;
	char	*after;
	char	*ret;

	before = check_malloc(ft_substr(str, 0, ith));
	after = check_malloc(ft_substr(str, ith + 1, ft_strlen(str)));
	ret = check_malloc(ft_strjoin(before, after));
	return (free(before), free(after), ret);
}

bool	search_space_quote_incre(char *str, int *i, char c)
{
	int		j;

	j = *i + 1;
	while (str[j])
	{
		if (str[j] && str[j] == c)
			return (false);
		if (str[j] && str[j] == ' ')
		{
			while (str[j])
			{
				if (str[j] == c)
					return (true);
				j++;
			}
		}
		j++;
	}
	return (false);
}

bool	search_space_quote_decre(char *str, int *i, char c)
{
	int		j;

	j = *i - 1;
	while (str[j] && str[j] != str[0])
	{
		if (str[j] && str[j] == c)
			return (false);
		if (str[j] && str[j] == ' ')
		{
			while (str[j] && j != 0)
			{
				if (str[j] == c)
					return (true);
				j--;
			}
		}
		j--;
	}
	return (false);
}
