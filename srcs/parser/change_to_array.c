/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_to_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshimurahiro <yoshimurahiro@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 11:51:33 by yoshimurahi       #+#    #+#             */
/*   Updated: 2023/12/06 11:07:29 by yoshimurahi      ###   ########.fr       */
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
	// else if (token == SEMICOLON)
	// 	return (";");
	else if (token == AND_AND)
		return ("&&");
	else if (token == OR_OR)
		return ("||");
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

// char	**change_to_array(t_tools *tools)
// {
// 	char **tmparray;
// 	char *tmpstr;
// 	int i;
// 	int k;
// 	t_simple_cmds *tmp;

// 	i = 0;
// 	k = 0;
// 	tmp = tools->simple_cmds;
// 	while (tmp)
// 	{
// 		if (tmp->str)
// 			i++;
// 		if (tmp->redirections)
// 			i++;
// 		tmp = tmp->next;
// 	}
// 	nodefirst_ver_simple_cmds(&tmp);
// 	tmparray = check_malloc((char **)malloc(sizeof(char *) * (i + 1)));
// 	i = 0;
// 	tmp = tools->simple_cmds;
// 	while (tmp)
// 	{
// 		k = 0;
// 		tmpstr = ft_strdup("");
// 		if (tmp->str && tmp->str[k])
// 		{
// 			while (tmp->str[k])
// 			{
// 				// if(tmpstr && tmp->redirections->token != 1)
// 					tmparray[i] = ft_strjoin(tmpstr, tmp->str[k]);
// 				if (tmp->str[k + 1])
// 					tmparray[i] = ft_strjoin(tmparray[i], " ");
// 				// if(tmpstr)
// 				// 	free(tmpstr);//これがないと、パイプが現れない問題
// 				tmpstr = ft_strdup(tmparray[i]);
// 				k++;
// 			}
// 			if (tmpstr)
// 				free(tmpstr);
// 			i++;
// 		}
// 		if (tmp->redirections)
// 		{
// 			while (tmp->redirections && tmp->redirections->token != 1)
// 			{
// 				tmparray[i++] = ft_strdup(token_to_char(tmp->redirections->token));
// 				if(!tmp->redirections->str)
					
// 				tmparray[i++] = ft_strdup(tmp->redirections->str);
// 				tmp->redirections = tmp->redirections->next;
// 			}
// 			if (tmp->redirections && tmp->redirections->token == 1)
// 			{
// 				tmparray[i++] = ft_strdup(token_to_char(tmp->redirections->token));
// 			}
// 		}
// 		tmp = tmp->next;
// 	}
// 	tmparray[i] = NULL;
// 	nodefirst_ver_simple_cmds(&tmp);
// 	return (tmparray);
// }



char	**allocate_tmparray(t_tools *tools, int size)
{
	char	**tmparray;

	tmparray = check_malloc((char **)malloc(sizeof(char *) * (size + 1)));
	return (tmparray);
}

char	*process_str_concat(char *tmpstr, t_simple_cmds *tmp, int k)
{
	char	*result;

	result = ft_strjoin(tmpstr, tmp->str[k]);
	return (result);
}


int		process_str(char **tmparray, t_simple_cmds *tmp, int i)
{
	int	k;
	char	*tmpstr;

	k = 0;
	tmpstr = ft_strdup("");
	if (tmp->str && tmp->str[k])
	{
		while (tmp->str[k])
		{
			tmparray[i] = process_str_concat(tmpstr, tmp, k);
			if (tmp->str[k + 1])
				tmparray[i] = ft_strjoin(tmparray[i], " ");
			free(tmpstr);
			tmpstr = ft_strdup(tmparray[i]);
			k++;
		}
		free(tmpstr);
		i++;
	}
	return (i);
}

int		process_redirections(char **tmparray, t_simple_cmds *tmp, int i)
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
	return (i);
}

int fill_tmparray(t_tools *tools, char **tmparray)
{
    int i = 0;
    t_simple_cmds *tmp = tools->simple_cmds;

    while (tmp)
    {
        i = process_str(tmparray, tmp, i);
        i = process_redirections(tmparray, tmp, i);
        tmp = tmp->next;
    }

    return i;
}

int count_elements(t_tools *tools)
{
    int count = 0;
    t_simple_cmds *tmp = tools->simple_cmds;

    while (tmp)
    {
        if (tmp->str)
            count++;
        if (tmp->redirections)
            count++;
        tmp = tmp->next;
    }
    return count;
}

char **change_to_array(t_tools *tools)
{
    char **tmparray;
    t_simple_cmds *tmp;
    int i;

    i = count_elements(tools);
    tmparray = allocate_tmparray(tools, i);
    i = fill_tmparray(tools, tmparray);
	if(tmparray[i - 1][0] == '|')
		return (NULL);
    tmparray[i] = NULL;

    return tmparray;
}
