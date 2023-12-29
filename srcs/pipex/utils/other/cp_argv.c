/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cp_argv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 22:33:19 by toshota           #+#    #+#             */
/*   Updated: 2023/12/11 15:04:18 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_element_count(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

void	cp_argv(char **argv, t_pipex *pipex)
{
	int	arg_i;

	pipex->argv = (char **)check_malloc \
	(malloc(sizeof(char *) * (get_element_count(argv) + 1)));
	arg_i = 0;
	while (argv[arg_i])
	{
		pipex->argv[arg_i] = check_malloc(ft_strdup(argv[arg_i]));
		arg_i++;
	}
	pipex->argv[arg_i] = NULL;
}
