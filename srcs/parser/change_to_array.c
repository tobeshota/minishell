/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_to_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjia <cjia@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 11:51:33 by yoshimurahi       #+#    #+#             */
/*   Updated: 2023/12/01 15:41:33 by cjia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*token_to_char(t_tokens token)
{
	if (token == PIPE)
		return ("|");
	else if (token == GREAT)
		return (">");
	else if (token == GREAT_GREAT)
		return (">>");
	else if (token == LESS)
		return ("<");
	else if (token == LESS_LESS)
		return ("<<");
	else
		return ("");
}

void	nodefirst_ver_simple_cmds(t_simple_cmds **node)
{
	if (node == NULL || *node == NULL)
		return ;
	while ((*node)->prev != NULL)
		*node = (*node)->prev;
}

char	**change_to_array(t_tools *tools)
{
	char **tmparray;
	char *tmpstr;
	int i;
	int k;
	t_simple_cmds *tmp;

	i = 0;
	k = 0;
	tmp = tools->simple_cmds;
	tmpstr = ft_strdup("");
	while (tmp)
	{
		if (tmp->str)
			i++;
		if (tmp->redirections)
			i++;
		tmp = tmp->next;
	}
	nodefirst_ver_simple_cmds(&tmp);
	tmparray = check_malloc((char **)malloc(sizeof(char *) * (i + 1)));
	i = 0;
	tmp = tools->simple_cmds;
	while (tmp)
	{
		k = 0;
		if (tmp->str && tmp->str[k])
		{
			while (tmp->str[k])
			{
				tmparray[i] = ft_strjoin(tmpstr, tmp->str[k]);
				if (tmp->str[k + 1])
					tmparray[i] = ft_strjoin(tmparray[i], " ");
				free(tmpstr);
				tmpstr = ft_strdup(tmp->str[k]);
				k++;
			}
			free(tmpstr);
			i++;
		}
		if (tmp->redirections)
		{
			while (tmp->redirections && tmp->redirections->token != 1)
			{
				tmparray[i++] = ft_strdup(token_to_char(tmp->redirections->token));
				tmparray[i++] = ft_strdup(tmp->redirections->str);
				tmp->redirections = tmp->redirections->next;
			}
			if (tmp->redirections && tmp->redirections->token == 1)
			{
				tmparray[i++] = ft_strdup(token_to_char(tmp->redirections->token));
			}
		}
		tmp = tmp->next;
	}
	tmparray[i] = NULL;
	nodefirst_ver_simple_cmds(&tmp);
	return (tmparray);
}