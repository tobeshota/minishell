/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_splitter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 12:45:31 by toshota           #+#    #+#             */
/*   Updated: 2023/12/04 12:45:40 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_splitter(char **argv)
{
	char	**splitter;
	int		sp_i;

	splitter = (char **)check_malloc(malloc(sizeof(char *)
				* (get_splitter_count(argv) + 1)));
	sp_i = 0;
	while (*argv)
	{
		if (is_specified_splitter(*argv))
			splitter[sp_i++] = check_malloc(ft_strdup(*argv));
		argv++;
	}
	splitter[sp_i] = NULL;
	return (splitter);
}
