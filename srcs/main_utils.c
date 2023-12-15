/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjia <cjia@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 11:36:00 by yoshimurahi       #+#    #+#             */
/*   Updated: 2023/12/15 12:24:06 by cjia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "minishell.h"

int	find_matching_quote(char *line, int i, int *num, int del)
{
	int	j;

	j = i + 1;
	*num += 1;
	while (line[j] && line[j] != del)
		j++;
	if (line[j] == del)
		*num += 1;
	return (j - i);
}

int	count_quotes(char *line)
{
	int	i;
	int	s;
	int	d;

	s = 0;
	d = 0;
	i = -1;
	while (line[++i])
	{
		if (line[i] == 34)
			i += find_matching_quote(line, i, &d, 34);
		if (line[i] == 39)
			i += find_matching_quote(line, i, &s, 39);
	}
	if ((d > 0 && d % 2 != 0) || (s > 0 && s % 2 != 0))
		return (0);
	return (1);
}

bool	ft_simple_cmdsclear(t_simple_cmds **simple_cmds)
{
	t_simple_cmds	*tmp;

	if (!*simple_cmds)
		return (false);
	while (*simple_cmds)
	{
		tmp = (*simple_cmds)->next;
		ft_lexerclear(&(*simple_cmds)->redirections);
		if ((*simple_cmds)->str)
			all_free_tab((*simple_cmds)->str);
		(*simple_cmds)->prev = NULL;
		if (*simple_cmds)
			free(*simple_cmds);
		*simple_cmds = tmp;
	}
	*simple_cmds = NULL;
	return (true);
}

int	implement_tools(t_tools *tools)
{
	tools->simple_cmds = NULL;
	tools->lexer_list = NULL;
	tools->str = NULL;
	tools->tmp_array = NULL;
	g_global.stop_heredoc = 0;
	g_global.in_cmd = 0;
	g_global.in_heredoc = 0;
	return (1);
}

int	free_tools(t_tools *tools)
{
	free(tools->str);
	tools->str = NULL;
	if (ft_simple_cmdsclear(&tools->simple_cmds) == false)
		ft_lexerclear(&tools->lexer_list);
	implement_tools(tools);
	free(tools);
	return (1);
}
