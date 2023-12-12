/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshimurahiro <yoshimurahiro@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 11:36:00 by yoshimurahi       #+#    #+#             */
/*   Updated: 2023/12/12 14:17:06 by yoshimurahi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "minishell.h"

bool	ft_simple_cmdsclear(t_simple_cmds **simple_cmds)
{
	t_simple_cmds	*tmp;
	t_lexer			*redirections_tmp;

	if (!*simple_cmds)
		return (false);
	while (*simple_cmds)
	{
		tmp = (*simple_cmds)->next;
		redirections_tmp = (*simple_cmds)->redirections;
		ft_lexerclear(&redirections_tmp);
		if ((*simple_cmds)->str)
			all_free_tab((*simple_cmds)->str);
		// free((*simple_cmds)->prev);
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

void	ft_lexerclear(t_lexer **lst)
{
	t_lexer	*tmp;

	if (!*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		if ((*lst)->str)
		{
			free((*lst)->str);
			(*lst)->str = NULL;
		}
		if (*lst)
		{
			free(*lst);
		}
		*lst = tmp;
	}
	*lst = NULL;
}
