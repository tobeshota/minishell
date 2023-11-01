/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshimurahiro <yoshimurahiro@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 13:32:45 by cjia              #+#    #+#             */
/*   Updated: 2023/11/01 09:53:09 by yoshimurahi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"

static size_t	calculate_sub_length(size_t s_len, unsigned int start,
		size_t len)
{
	size_t	sub_len;

	sub_len = len;
	if (sub_len > (s_len - start))
	{
		sub_len = s_len - start;
	}
	return (sub_len);
}

static char	*allocate_and_fill_substring(const char *s, unsigned int start,
		size_t sub_len)
{
	char	*sub_str;
	size_t	i;

	i = 0;
	sub_str = (char *)malloc((sub_len + 1) * sizeof(char));
	if (sub_str == NULL)
	{
		return (NULL);
	}
	while (i < sub_len)
	{
		sub_str[i] = s[start + i];
		i++;
	}
	sub_str[sub_len] = '\0';
	return (sub_str);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*empty_str;
	size_t	sub_len;

	if (s == NULL)
	{
		return (NULL);
	}
	s_len = ft_strlen(s);
	if (start >= s_len)
	{
		empty_str = (char *)malloc(1);
		if (empty_str != NULL)
		{
			empty_str[0] = '\0';
		}
		return (empty_str);
	}
	sub_len = calculate_sub_length(s_len, start, len);
	return (allocate_and_fill_substring(s, start, sub_len));
}
