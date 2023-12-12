/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshimurahiro <yoshimurahiro@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:39:54 by yoshimurahi       #+#    #+#             */
/*   Updated: 2023/12/12 19:46:16 by yoshimurahi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "minishell.h"
#include "pipex.h"

char	*delete_quotes(char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			j = 0;
			while (str[i + j] == c)
				j++;
			ft_strlcpy(&str[i], &str[i + j], strlen(str) - i);
		}
		i++;
	}
	return (str);
}

int	handle_digit_after_dollar(int j, char *str)
{
	int	i;

	i = j;
	if (str[j] == '$')
	{
		if (ft_isdigit(str[j + 1]) == 1)
		{
			j += 2;
		}
	}
	return (j - i);
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
		else if (str[j] == '$' && (str[j + 1] != ' ' && (str[j + 1] != '"'
						|| str[j + 2] != '\0')) && str[j + 1] != '\0')
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
		// if (ft_strncmp(str[0], "export", ft_strlen(str[0]) - 1) != 0)
		// {
		// 	str[i] = delete_quotes(str[i], '\"');
		// 	str[i] = delete_quotes(str[i], '\'');
		// }
		i++;
	}
	free_old_str(tools);
	return (str);
}
