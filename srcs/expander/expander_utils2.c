/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshimurahiro <yoshimurahiro@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 09:35:08 by yoshimurahi       #+#    #+#             */
/*   Updated: 2023/12/09 21:30:38 by yoshimurahi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/expander.h"

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
		if (ft_strncmp(str + j + 1, envp[k], find_equal(envp[k])
				- 1) == 0 && after_dol_lenght(str, j)
			- j == (int)find_equal(envp[k]))
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

int	question_mark(char **tmp)
{
	free(*tmp);
	*tmp = ft_itoa(g_global.error_num);
	return (ft_strlen(*tmp) + 1);
}

// int	question_mark(char **tmp)
// {
// 	char *tmp2;
// 	free(*tmp);
// 	tmp2 = ft_itoa(g_global.error_num);
// 	*tmp = ft_strjoin("echo ", tmp2);
// 	free(tmp2);
// 	return (ft_strlen(*tmp) + 1);
// }
