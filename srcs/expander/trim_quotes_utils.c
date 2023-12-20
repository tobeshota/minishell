/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quotes_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjia <cjia@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 17:27:15 by cjia              #+#    #+#             */
/*   Updated: 2023/12/20 17:28:05 by cjia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "minishell.h"

// 文字列中のi番目の文字を付け加える
char    *add_ith_c(char *str, char add, int ith)
{
    char    add_str[2];
    char    *before;
    char    *before_w_add;
    char    *after;
    char    *ret;

    add_str[0] = add;
    add_str[1] = '\0';
    before = check_malloc(ft_substr(str, 0, ith));
    after = check_malloc(ft_substr(str, ith, ft_strlen(str)));
    before_w_add = check_malloc(ft_strjoin(before, add_str));
    ret = check_malloc(ft_strjoin(before_w_add, after));
    return (free(before), free(after), free(before_w_add), ret);
}

// 文字列中のi番目の文字を消す
char    *omit_ith_c(char *str, int ith)
{
    char    *before;
    char    *after;
    char    *ret;

    before = check_malloc(ft_substr(str, 0, ith));
    after = check_malloc(ft_substr(str, ith + 1, ft_strlen(str)));
    ret = check_malloc(ft_strjoin(before, after));
    return (free(before), free(after), ret);
}

bool  	search_space_quote_incre(char *str, int *i, char c)
{
  int		j;
  int 		frag;

  j = *i + 1;
  while(str[j])
  {
	if(str[j] && str[j] == '"')
		return (false);
	if (str[j] && str[j] == ' ')
	{
		frag = 1;
		while (str[j])
		{
			if (str[j] == c)
				return (true);
			j++;
		}
	}
	j++;
  }
  if(frag == 0)
	  return (true);
	return (false);
}



bool  	search_space_quote_decre(char *str, int *i, char c)
{
	int		j;
	int 		frag;

	j = *i - 1;
	frag = 0;
	while(str[j] && str[j] != str[0])
	{
		if(str[j] && str[j] == '"')
			return (false);
		if (str[j] && str[j] == ' ' && frag == 0)
		{
			frag = 1;
			while (str[j] && j != 0)
			{
				if (str[j] == c)
					return (true);
				j--;
			}
		}
		j--;
	}
	if(frag == 0)
		return (true);
	return (false);
}
