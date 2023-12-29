/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 00:14:56 by toshota           #+#    #+#             */
/*   Updated: 2023/12/29 12:01:33 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*double_to_sigle(char **array, char splitter)
{
	char	*str;
	char	splitter_str[2];
	char	*tmp;
	int		i;

	str = NULL;
	splitter_str[0] = splitter;
	splitter_str[1] = '\0';
	i = 0;
	while (array[i])
	{
		tmp = str;
		str = check_malloc(ft_strjoin(str, array[i]));
		free(tmp);
		if (array[i + 1])
		{
			tmp = str;
			str = check_malloc(ft_strjoin(str, splitter_str));
			free(tmp);
		}
		i++;
	}
	return (str);
}

size_t	strlen_until_c(char *str, char c)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0' && str[len] != c)
		len++;
	return (len);
}
