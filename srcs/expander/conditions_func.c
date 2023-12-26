/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshimurahiro <yoshimurahiro@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 17:25:17 by cjia              #+#    #+#             */
/*   Updated: 2023/12/26 18:24:10 by yoshimurahi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "minishell.h"

bool	first_quote(char *str, int *i, char c)
{
	int		j;
	int		num;

	j = *i;
	num = 0;
	while (str[num])
	{
		if (str[num] == c)
		{
			if (num == j)
				return (true);
			else
				return (false);
		}
		num++;
	}
	return (false);
}

bool	last_quote(char *str, int *i, char c)
{
	int		j;
	int		num;

	j = *i;
	num = 0;
	num = ft_strlen(str) - 1;
	while (str[num] && num != 0)
	{
		if (str[num] == c)
		{
			if (num == j)
				return (true);
			else
				return (false);
		}
		num--;
	}
	return (false);
}

void	judge_opp_frag(char *str, int opp, int *opp_quote_frags, int *i)
{
	if (str[(*i)] == opp && *opp_quote_frags == 0)
		*opp_quote_frags = 1;
	else if (str[(*i)] == opp && *opp_quote_frags == 1)
		*opp_quote_frags = 0;
}
