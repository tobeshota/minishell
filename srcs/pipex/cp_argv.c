/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cp_argv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 22:33:19 by toshota           #+#    #+#             */
/*   Updated: 2023/12/10 22:33:24 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	get_argc(char **argv)
{
	int	argc;

	argc = 0;
	while (argv[argc])
		argc++;
	return (argc);
}

void	cp_argv(char **argv, t_pipex *pipex)
{
	int	arg_i;

	pipex->argv = (char **)check_malloc \
	(malloc(sizeof(char *) * (get_argc(argv) + 1)));
	arg_i = 0;
	while (argv[arg_i])
	{
		pipex->argv[arg_i] = check_malloc(ft_strdup(argv[arg_i]));
		arg_i++;
	}
	pipex->argv[arg_i] = NULL;
}
