/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshimurahiro <yoshimurahiro@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 11:36:00 by yoshimurahi       #+#    #+#             */
/*   Updated: 2023/12/13 17:04:58 by yoshimurahi      ###   ########.fr       */
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
		if(*simple_cmds)
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

char	**ft_arrdup(char **arr)
{
	char	**rtn;
	size_t	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	rtn = ft_calloc(sizeof(char *), i + 1);
	if (!rtn)
		return (NULL);
	i = 0;
	while (arr[i] != NULL)
	{
		rtn[i] = ft_strdup(arr[i]);
		if (rtn[i] == NULL)
		{
			all_free_tab(rtn);
			return (rtn);
		}
		i++;
	}
	return (rtn);
}

void	ft_nodefirst_for_lexer(t_lexer **node)
{
	if (node == NULL || *node == NULL)
		return ;
	while ((*node)->prev != NULL)
		*node = (*node)->prev;
}

void	ft_lexerclear(t_lexer **lst)
{
	t_lexer	*tmp;

	if (!*lst)
		return ;
	while (*lst)
	{
		if((*lst)->next)
			tmp = (*lst)->next;
		else
			tmp = NULL;
		if ((*lst)->str)
		{	
			free((*lst)->str);
			(*lst)->str = NULL;
		}
		if (*lst)
		{
			if ((*lst)->next == NULL)
				break ;
			free(*lst);
			*lst = NULL;
		}
		*lst = tmp;
	}
	ft_nodefirst_for_lexer(lst);
	lst = NULL;
}
