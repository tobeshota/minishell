/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshimurahiro <yoshimurahiro@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 17:20:33 by cjia              #+#    #+#             */
/*   Updated: 2023/12/26 11:21:04 by yoshimurahi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "minishell.h"

char	*move_to_first(char *str, char c, char opp)
{
	int		i;
	int		frags;
	int		opp_quote_frags;
	char	*tmp;
	char	*tmp2;

	i = 0;
	frags = 0;
	opp_quote_frags = 0;
	tmp = NULL;
	tmp2 = NULL;
	i = ft_strlen(str) - 1;
	while (i > 0 && str[i])
	{
		if (str[i] == opp && opp_quote_frags == 0)
			opp_quote_frags = 1;
		else if (str[i] == opp && opp_quote_frags == 1)
			opp_quote_frags = 0;
		if (str[i] == c && frags == 0 && i > 0 && opp_quote_frags == 0)
			frags = 1;
		else if (str[i] == c && frags == 1 && i > 0
			&& str[i - 1] != ' ' && str[i - 1] != opp
			&& opp_quote_frags == 0)
		{
			tmp = omit_ith_c(str, i);
			i--;
			while (str[i])
			{
				if (str[i - 1] == ' ' || i == 0 || str[i] == '\0')
				{
					tmp2 = add_ith_c(tmp, c, i);
					i--;
					free(tmp);
					tmp = NULL;
					free(str);
					str = tmp2;
					break ;
				}
				i--;
			}
			frags = 0;
		}
		else if (str[i] == c && frags == 1 && i > 0
			&& (str[i - 1] == ' ' || str[i - 1] == opp) && opp_quote_frags == 0)
			frags = 0;
		i--;
	}
	if (tmp)
		free(tmp);
	return (str);
}

char	*move_to_last(char *str, char c, char opp)
{
	int		i;
	int		frags;
	int		opp_quote_frags;
	int		len;
	int		j;
	char	*tmp;
	char	*tmp2;

	i = 0;
	frags = 0;
	j = 0;
	opp_quote_frags = 0;
	tmp = NULL;
	tmp2 = NULL;
	len = ft_strlen(str) - 1;
	while (str && str[i] != '\0')
	{
		if (str[i] == opp && opp_quote_frags == 0)
			opp_quote_frags = 1;
		else if (str[i] == opp && opp_quote_frags == 1)
			opp_quote_frags = 0;
		if (str[i] == c && frags == 0 && opp_quote_frags == 0)
			frags = 1;
		else if (str[i] == c && frags == 1 && i < len - 1
			&& str[i + 1] != ' ' && str[i + 1] != opp && opp_quote_frags == 0)
		{
			tmp = omit_ith_c(str, i);
			i++;
			while (str[i])
			{
				if (str[i + 1] == ' ' || str[i + 1] == '\0')
				{
					j++;
					tmp2 = add_ith_c(tmp, c, i - j + 1);
					i++;
					free(tmp);
					tmp = NULL;
					free(str);
					str = tmp2;
					break ;
				}
				i++;
			}
			frags = 0;
		}
		else if (str[i] == c && frags == 1 && i < len - 1
			&& (str[i + 1] == ' ' || str[i + 1] == opp) && opp_quote_frags == 0)
			frags = 0;
		i++;
	}
	if (tmp)
		free(tmp);
	return (str);
}
