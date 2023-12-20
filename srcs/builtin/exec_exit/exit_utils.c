/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 22:33:45 by toshota           #+#    #+#             */
/*   Updated: 2023/12/20 22:38:27 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "expander.h"
#define OVERFLOW_ULL -42

static bool	is_overflow_ull(unsigned long long ullnb, const char *str)
{
	int					addend;
	unsigned long long	lmax_div;
	int					lmax_mod;

	lmax_div = ULLONG_MAX / 10;
	lmax_mod = ULLONG_MAX % 10;
	addend = *str - '0';
	return (ullnb > lmax_div || \
	(ullnb == lmax_div && addend > lmax_mod));
}

unsigned long long	ascii_to_abs_ull(const char *str, int *sign)
{
	unsigned long long	ullnb;

	*sign = 1;
	ullnb = 0;
	if (*str == '-')
		*sign = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (ft_isdigit(*str))
	{
		if (is_overflow_ull(ullnb, str))
		{
			*sign = OVERFLOW_ULL;
			break ;
		}
		ullnb = (ullnb * 10) + (*str - '0');
		str++;
	}
	return (ullnb);
}
