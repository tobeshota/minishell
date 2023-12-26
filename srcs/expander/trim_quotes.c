/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshimurahiro <yoshimurahiro@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 17:20:33 by cjia              #+#    #+#             */
/*   Updated: 2023/12/26 18:24:00 by yoshimurahi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "minishell.h"

char	*omit_and_add_ver_last(char *str, int c, int *i, int *j)
{
	char	*tmp;
	char	*tmp2;

	tmp = omit_ith_c(str, *i);
	(*i)++;
	while (str[(*i)])
	{
		if (str[(*i) + 1] == ' ' || str[(*i) + 1] == '\0')
		{
			(*j)++;
			tmp2 = add_ith_c(tmp, c, (*i) - (*j) + 1);
			(*i)++;
			free(tmp);
			free(str);
			str = tmp2;
			break ;
		}
		(*i)++;
	}
	return (str);
}

char	*move_to_last(char *str, char c, char opp)
{
	int		i;
	int		frags;
	int		opp_quote_frags;
	int		len;
	int		j;

	len = ft_strlen(str) - 1;
	init_move_to_last(&i, &frags, &opp_quote_frags, &j);
	while (str && str[i] != '\0')
	{
		judge_opp_frag(str, opp, &opp_quote_frags, &i);
		if (str[i] == c && frags == 0 && opp_quote_frags == 0)
			frags = 1;
		else if (str[i] == c && frags == 1 && i <= len - 1
			&& str[i + 1] != ' ' && str[i + 1] != opp && opp_quote_frags == 0)
		{
			str = omit_and_add_ver_last(str, c, &i, &j);
			frags = 0;
		}
		else if (str[i] == c && frags == 1 && i < len - 1
			&& (str[i + 1] == ' ' || str[i + 1] == opp) && opp_quote_frags == 0)
			frags = 0;
		i++;
	}
	return (str);
}

void	init_move_to_first(int *i, int *frags, int *opp_quote_frags, char *str)
{
	*i = ft_strlen(str) - 1;
	*frags = 0;
	*opp_quote_frags = 0;
}

char	*omit_and_add(char *str, char c, int *i)
{
	char	*tmp;
	char	*tmp2;

	tmp = omit_ith_c(str, *i);
	(*i)--;
	while ((*i) > 0 && str[(*i) - 1] != ' ')
		(*i)--;
	tmp2 = add_ith_c(tmp, c, *i);
	(*i)--;
	free(tmp);
	free(str);
	return (tmp2);
}

char	*move_to_first(char *str, char c, char opp)
{
	int		i;
	int		frags;
	int		opp_quote_frags;

	init_move_to_first(&i, &frags, &opp_quote_frags, str);
	while (i > 0 && str[i])
	{
		if (str[i] == opp && opp_quote_frags == 0)
			opp_quote_frags = 1;
		else if (str[i] == opp && opp_quote_frags == 1)
			opp_quote_frags = 0;
		if (str[i] == c && frags == 0 && i > 0 && opp_quote_frags == 0)
			frags = 1;
		else if (str[i] == c && frags == 1 && i > 0
			&& str[i - 1] != ' ' && str[i - 1] != opp && opp_quote_frags == 0)
		{
			str = omit_and_add(str, c, &i);
			frags = 0;
		}
		else if (str[i] == c && frags == 1 && i > 0
			&& (str[i - 1] == ' ' || str[i - 1] == opp) && opp_quote_frags == 0)
			frags = 0;
		i--;
	}
	return (str);
}
