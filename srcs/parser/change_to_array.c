/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_to_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjia <cjia@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 11:51:33 by yoshimurahi       #+#    #+#             */
/*   Updated: 2023/12/15 11:31:12 by cjia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int	fill_tmparray(t_tools *tools, char **tmparray)
{
	int				i;
	t_simple_cmds	*tmp;

	i = 0;
	tmp = tools->simple_cmds;
	while (tmp)
	{
		i = process_redirection_str(tmparray, tmp, i);
		i = process_redirections(tmparray, tmp, i);
		tmp = tmp->next;
	}
	return (i);
}

char	**allocate_tmparray(int size)
{
	char	**tmparray;

	tmparray = check_malloc((char **)malloc(sizeof(char *) * (size + 1)));
	return (tmparray);
}

int	count_elements(t_tools *tools)
{
	int				count;
	t_simple_cmds	*tmp;
	t_lexer			*tmp2;

	count = 0;
	tmp = tools->simple_cmds;
	while (tmp)
	{
		if (tmp->str)
			count++;
		tmp2 = tmp->redirections;
		while (tmp2)
		{
			if (tmp2->str)
				count++;
			if (tmp2->token)
				count++;
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
	return (count);
}

char	**change_to_array(t_tools *tools)
{
	char	**tmparray;
	int		i;

	i = count_elements(tools);
	tmparray = allocate_tmparray(i);
	i = fill_tmparray(tools, tmparray);
	tmparray[i] = NULL;
	return (tmparray);
}
