/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshimurahiro <yoshimurahiro@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 10:11:50 by yoshimurahi       #+#    #+#             */
/*   Updated: 2023/12/26 11:05:59 by yoshimurahi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/expander.h"

int	handle_digit_after_dollar(int j, char *str)
{
	int	i;

	i = j;
	if (str[j] == '$')
	{
		if (ft_isdigit(str[j + 1]) == 1)
		{
			j += 2;
		}
	}
	return (j - i);
}

char	*char_to_str(char c)
{
	char	*str;

	str = ft_calloc(sizeof(char), 2);
	str[0] = c;
	return (str);
}

int	after_dol_lenght(char *str, int j)
{
	int	i;

	i = j + 1;
	while (str[i] != '\0' && str[i] != '$' && str[i] != ' '
		&& str[i] != '\"' && str[i] != '\'' && str[i] != '=' && str[i] != '-'
		&& str[i] != ':' && str[i] != '|' && str[i] != ';' && str[i] != '/'
		&& str[i] != '\t' && str[i] != '\n')
		i++;
	return (i);
}

int	strlen_between_c(char *str, char c)
{
	char	*str_after_1st_c;
	char	*str_after_2nd_c;

	str_after_1st_c = ft_strchr(str, c) + 1;
	str_after_2nd_c = ft_strchr(str_after_1st_c, c);
	return (str_after_2nd_c - str_after_1st_c);
}
