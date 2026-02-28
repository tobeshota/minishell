/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard_utils1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobeshota <tobeshota@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 16:43:07 by toshota           #+#    #+#             */
/*   Updated: 2026/02/28 17:34:44 by tobeshota        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static char	get_backward_encloser(char *backward)
{
	size_t	i;

	i = 0;
	while (backward[i])
	{
		if (backward[i] == '\'' || backward[i] == '\"')
			return (backward[i]);
		i++;
	}
	return ('\0');
}

static char	get_prefix_encloser(char *prefix)
{
	size_t	i;

	if (ft_strlen(prefix) == 0)
		return ('\0');
	i = ft_strlen(prefix) - 1;
	while (i != 0)
	{
		if (prefix[i] == '\'' || prefix[i] == '\"')
			return (prefix[i]);
		i--;
	}
	return ('\0');
}

static bool	is_asterisk_special_character(char *str)
{
	char	*prefix;
	char	*backward;
	char	b_encloser_closest_to_asterisk;
	char	p_encloser_closest_to_asterisk;

	prefix = check_malloc(ft_substr(str, 0, strlen_until_c(str, '*')));
	backward = check_malloc(ft_strdup(ft_strrchr(str, '*') + 1));
	p_encloser_closest_to_asterisk = get_prefix_encloser(prefix);
	b_encloser_closest_to_asterisk = get_backward_encloser(backward);
	if (b_encloser_closest_to_asterisk == '\0' || \
		p_encloser_closest_to_asterisk == '\0')
		return (free(prefix), free(backward), true);
	if (p_encloser_closest_to_asterisk == b_encloser_closest_to_asterisk)
		return (free(prefix), free(backward), false);
	return (free(prefix), free(backward), true);
}

bool	is_specified_wildcard(char *str)
{
	if (ft_strchr(str, '*') == NULL)
		return (false);
	if (is_file_exist(str) == true)
		return (false);
	if (is_asterisk_special_character(str) == false)
		return (false);
	return (true);
}
