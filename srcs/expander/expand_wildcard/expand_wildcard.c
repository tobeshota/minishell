/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 16:43:07 by toshota           #+#    #+#             */
/*   Updated: 2023/12/19 00:22:14 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

bool	is_specified_wildcard(char *str)
{
	if (ft_strchr(str, '*') == NULL)
		return (false);
	if (is_file_exist(str) == true)
		return (false);
	return (true);
}

void	expand_wildcard(char **h_argv)
{
	int	arg_i;

	arg_i = 0;
	while (h_argv[arg_i])
	{
		if (is_specified_wildcard(h_argv[arg_i]))
			expand_argv_w_wildcard(&h_argv[arg_i]);
		arg_i++;
	}
}
