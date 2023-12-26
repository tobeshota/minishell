/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_dollar_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshimurahiro <yoshimurahiro@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 10:35:37 by cjia              #+#    #+#             */
/*   Updated: 2023/12/26 10:29:56 by yoshimurahi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/expander.h"

bool	check_conditions(char *str, int j)
{
	return (str[j] == '$'
		&& (str[j + 1] != ' ') && str[j + 1] != '\0'
		&& str[j + 1] != '/' && str[j + 1] != '-');
}

size_t	find_equal(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i + 1);
		i++;
	}
	return (0);
}

size_t	find_dollar(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (i + 1);
		i++;
	}
	return (0);
}

int	loop_if_dollar_sign(char **envp, char *str, char **tmp, int j)
{
	int		k;
	int		ret;
	char	*tmp2;
	char	*tmp3;

	k = 0;
	ret = 0;
	while (envp[k])
	{
		if (ft_strncmp(str + j + 1, envp[k], find_equal(envp[k]) - 1) == 0
			&& after_dol_lenght(str, j) - j == (int)find_equal(envp[k]))
		{
			tmp2 = ft_strdup(envp[k] + find_equal(envp[k]));
			tmp3 = ft_strjoin(*tmp, tmp2);
			free(*tmp);
			*tmp = tmp3;
			free(tmp2);
			ret = find_equal(envp[k]);
		}
		k++;
	}
	if (ret == 0)
		ret = after_dol_lenght(str, j) - j;
	return (ret);
}

int	question_mark(char **tmp, t_tools *tools)
{
	char	*tmp2;
	char	*tmp3;

	tmp2 = ft_itoa(tools->error_num);
	tmp3 = ft_strjoin(*tmp, tmp2);
	free(*tmp);
	*tmp = tmp3;
	free(tmp2);
	return (2);
}
