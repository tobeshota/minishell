/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshimurahiro <yoshimurahiro@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:39:54 by yoshimurahi       #+#    #+#             */
/*   Updated: 2023/12/26 11:00:47 by yoshimurahi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "minishell.h"
#include "pipex.h"

void	ft_nodefirst_for_t_simple_cmds(t_simple_cmds **node)
{
	if (node == NULL || *node == NULL)
		return ;
	while ((*node)->prev != NULL)
		*node = (*node)->prev;
}

void	free_old_str(t_tools *tools)
{
	while (tools->simple_cmds->str)
	{
		all_free_tab(tools->simple_cmds->str);
		tools->simple_cmds->str = NULL;
		if (tools->simple_cmds->next == NULL)
			break ;
		tools->simple_cmds = tools->simple_cmds->next;
	}
	ft_nodefirst_for_t_simple_cmds(&tools->simple_cmds);
}

bool	check_case_herecoc(char **str, int i)
{
	char	*tmp;

	if (str[i + 1] && is_match(str[i], "<<") == true
		&& str[i + 1] != (void *) '\0')
	{
		tmp = check_malloc(ft_strdup(str[i]));
		free(str[i]);
		str[i] = tmp;
		tmp = check_malloc(ft_strdup(str[i + 1]));
		free(str[i + 1]);
		str[i + 1] = tmp;
		return (true);
	}
	return (false);
}

char	**expander(t_tools *tools, char **str, char **envp)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (str[i] != NULL)
	{
		if (check_case_herecoc(str, i) == true)
			i++;
		else
		{
			tmp = process_dollar_quote(str[i], envp, tools);
			free(str[i]);
			str[i] = tmp;
		}
		i++;
	}
	free_old_str(tools);
	expand_wildcard(str);
	return (str);
}
