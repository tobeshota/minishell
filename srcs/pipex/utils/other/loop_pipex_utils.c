/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_pipex_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 09:23:37 by toshota           #+#    #+#             */
/*   Updated: 2023/12/04 12:51:02 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	is_specified_splitter(char *str)
{
	return (is_match(str, ";") || is_match(str, "&&") || is_match(str, "||"));
}

int	get_splitter_count(char **argv)
{
	int	splitter_count;
	int	arg_i;

	splitter_count = 0;
	arg_i = 0;
	while (argv[arg_i])
	{
		if (is_specified_splitter(argv[arg_i]))
			splitter_count++;
		arg_i++;
	}
	return (splitter_count);
}

bool	is_splitter_exist(char **argv)
{
	int	arg_i;

	arg_i = 0;
	while (argv[arg_i])
	{
		if (is_specified_splitter(argv[arg_i]) == true)
			return (true);
		arg_i++;
	}
	return (false);
}
