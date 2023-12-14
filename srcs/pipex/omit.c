/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   omit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 20:38:49 by toshota           #+#    #+#             */
/*   Updated: 2023/12/13 22:24:06 by toshota          ###   ########.fr       */
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

char	**omit_array(char **array, char *omit, bool is_str_malloced)
{
	int		i;
	char	*tmp;

	i = 0;
	if (is_str_malloced == true)
	{
		while (array[i])
		{
			tmp = array[i];
			array[i] = omit_str(array[i], omit);
			free(tmp);
			i++;
		}
	}
	else
	{
		while (array[i])
		{
			array[i] = omit_str(array[i], omit);
			i++;
		}
	}
	return (array);
}

char	*omit_quotas(char *str, bool is_str_malloced)
{
	char	*tmp;

	if (is_str_malloced == true)
	{
		tmp = str;
		str = omit_str(str, "\'\"");
		free(tmp);
	}
	else
	{
		str = omit_str(str, "\'\"");
	}
	return (str);
}
