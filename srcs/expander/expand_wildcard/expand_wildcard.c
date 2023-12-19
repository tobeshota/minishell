/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 16:43:07 by toshota           #+#    #+#             */
/*   Updated: 2023/12/19 09:43:35 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

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
