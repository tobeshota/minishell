/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjia <cjia@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:11:42 by yoshimurahi       #+#    #+#             */
/*   Updated: 2023/12/29 11:14:01 by cjia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	skip(char *str, int i)
{
	int	j;

	j = 0;
	while (str[j + i] == ' ' || (str[j + i] >= 9 && str[j + i] <= 13))
		j++;
	return (j);
}

static int	process_str(int index, t_tools *tools)
{
	int	i;
	int	j;

	i = index;
	j = 0;
	i = i + skip(tools->str, i);
	if (check_token(tools->str, i))
		j = handle_token(tools->str, i, &tools->lexer_list);
	else
		j = word_in_node(tools->str, i, &tools->lexer_list);
	if (j < 0)
		return (0);
	i += j;
	return (i);
}

int	lexer(t_tools *tools)
{
	int	i;

	i = 0;
	while (tools->str[i])
	{
		i = process_str(i, tools);
		if (i == 0)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
