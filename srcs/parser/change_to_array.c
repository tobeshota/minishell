/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_to_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshimurahiro <yoshimurahiro@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 11:51:33 by yoshimurahi       #+#    #+#             */
/*   Updated: 2023/12/09 20:07:07 by yoshimurahi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

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
	else if (token == SEMICOLON)
		return (";");
	else if (token == AND_AND)
		return ("&&");
	else if (token == OR_OR)
		return ("||");
	else
		return ("");
}

char	*process_str_concat(char *tmpstr, char *str)
{
	char	*result;

	result = check_malloc(ft_strjoin(tmpstr, str));
	return (result);
}

int	process_str(char **tmparray, t_simple_cmds *tmp, int i)
{
	int		k;
	char	*tmpstr;

	k = 0;
	tmpstr = NULL;
	if (tmp->str && tmp->str[k])
	{
		tmparray[i] = process_str_concat(tmpstr, tmp->str[k]);
		while (tmp->str[k + 1])
		{
			tmpstr = check_malloc(ft_strjoin(tmparray[i], " "));
			free(tmparray[i]);
			tmparray[i] = check_malloc(ft_strjoin(tmpstr, tmp->str[k + 1]));
			free(tmpstr);
			k++;
		}
		i++;
	}
	return (i);
}

int	process_redirections(char **tmparray, t_simple_cmds *tmp, int i)
{
	while (tmp->redirections && tmp->redirections->token != PIPE
		&& tmp->redirections->token != AND_AND
		&& tmp->redirections->token != OR_OR
		&& tmp->redirections->token != SEMICOLON)
	{
		tmparray[i++] = ft_strdup(token_to_char(tmp->redirections->token));
		if (tmp->redirections->str)
		{
			tmparray[i++] = ft_strdup(tmp->redirections->str);
			free(tmp->redirections->str);
			free(tmp->redirections);
			tmp->redirections->str = NULL;
		}
		tmp->redirections = tmp->redirections->next;
	}
	if (tmp->redirections && (tmp->redirections->token == PIPE
			|| tmp->redirections->token == AND_AND
			|| tmp->redirections->token == OR_OR
			|| tmp->redirections->token == SEMICOLON))
	{
		tmparray[i++] = ft_strdup(token_to_char(tmp->redirections->token));
	}
	return (i);
}

int	fill_tmparray(t_tools *tools, char **tmparray)
{
	int				i;
	t_simple_cmds	*tmp;

	i = 0;
	tmp = tools->simple_cmds;
	while (tmp)
	{
		i = process_str(tmparray, tmp, i);
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

	count = 0;
	tmp = tools->simple_cmds;
	while (tmp)
	{
		if (tmp->str)
			count++;
		if (tmp->redirections)
			count++;
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
