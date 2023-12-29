/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   omit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 20:38:49 by toshota           #+#    #+#             */
/*   Updated: 2023/12/19 12:02:37 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static size_t	strlen_without_c(char *str, char c)
{
	int	i;
	int	len_without_c;

	i = 0;
	len_without_c = 0;
	while (str[i])
	{
		if (str[i] != c)
			len_without_c++;
		i++;
	}
	return (len_without_c);
}

char	*omit_c(char *str, char c)
{
	char	*str_without_c;
	int		i;

	str_without_c = (char *)check_malloc(malloc(sizeof(char)
				* (strlen_without_c(str, c) + 1)));
	i = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			str_without_c[i] = str[i];
			i++;
		}
		else
			str++;
	}
	str_without_c[i] = '\0';
	return (str_without_c);
}

char	*omit_str(char *str, char *omit)
{
	char	*tmp;
	char	*result;

	result = check_malloc(ft_strdup(str));
	while (*omit)
	{
		tmp = result;
		result = omit_c(result, *omit);
		free(tmp);
		omit++;
	}
	return (result);
}

char	**omit_array(char **array, char *omit)
{
	int		i;
	char	**result;

	i = 0;
	result = (char **)check_malloc \
	(malloc(sizeof(char *) * (get_element_count(array) + 1)));
	while (array[i])
	{
		result[i] = omit_str(array[i], omit);
		i++;
	}
	result[i] = NULL;
	return (result);
}
