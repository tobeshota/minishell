/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjia <cjia@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:39:54 by yoshimurahi       #+#    #+#             */
/*   Updated: 2023/12/15 12:32:28 by cjia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "minishell.h"
#include "pipex.h"

bool	title(char *str, int j)
{
	return (str[j] == '$'
		&& (str[j + 1] != ' ' && str[j + 1] != '$'
			&& (str[j + 1] != '"' || str[j + 2] != '\0'))
		&& str[j + 1] != '\0');
}

char	*detect_dollar(char *str, char **envp)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	j = 0;
	tmp = ft_strdup("\0");
	while (str[j])
	{
		j += handle_digit_after_dollar(j, str);
		if (str[j] == '$' && str[j + 1] == '?')
			j += question_mark(&tmp);
		else if (title(str, j) == true)
			j += loop_if_dollar_sign(envp, str, &tmp, j);
		else
		{
			tmp2 = char_to_str(str[j++]);
			tmp3 = ft_strjoin(tmp, tmp2);
			free(tmp);
			tmp = tmp3;
			free(tmp2);
		}
	}
	return (tmp);
}

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

char	**expander(t_tools *tools, char **str, char **envp)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (str[i] != NULL)
	{
		if (find_dollar(str[i]) != 0 && str[i][find_dollar(str[i]) - 2] != '\''
			&&
			str[i][find_dollar(str[i])] != '\0')
		{
			tmp = detect_dollar(str[i], envp);
			free(str[i]);
			str[i] = tmp;
		}
		i++;
	}
	free_old_str(tools);
	return (str);
}
