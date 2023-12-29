/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_splitted_argv.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 12:42:40 by toshota           #+#    #+#             */
/*   Updated: 2023/12/04 12:43:29 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	malloc_splitted_argv_double_ptr(char ***splitted_argv, char **argv)
{
	int	sparg_i;
	int	arg_i;

	sparg_i = 0;
	while (true)
	{
		arg_i = 0;
		while (argv[arg_i] && is_specified_splitter(argv[arg_i]) == false)
			arg_i++;
		if (argv[arg_i] == NULL && \
		is_specified_splitter(argv[arg_i - 1]) == true)
			break ;
		splitted_argv[sparg_i++] = (char **)check_malloc \
		(malloc((sizeof(char *) * (arg_i + 1))));
		if (argv[arg_i] == NULL)
			break ;
		argv += arg_i + 1;
	}
}

static int	get_splitted_argc(char **argv)
{
	int	arg_i;

	arg_i = 0;
	while (argv[arg_i])
		arg_i++;
	if (is_specified_splitter(argv[arg_i - 1]))
		return (get_splitter_count(argv));
	else
		return (get_splitter_count(argv) + 1);
}

char	***get_splitted_argv(char **argv)
{
	char	***splitted_argv;
	int		sparg_i;
	int		element_i;

	splitted_argv = (char ***)check_malloc(malloc(sizeof(char **)
				* (get_splitted_argc(argv) + 1)));
	malloc_splitted_argv_double_ptr(splitted_argv, argv);
	sparg_i = 0;
	while (*argv)
	{
		element_i = 0;
		while (*argv && is_specified_splitter(*argv) == false)
			splitted_argv[sparg_i][element_i++] = \
			check_malloc(ft_strdup(*argv++));
		splitted_argv[sparg_i++][element_i] = NULL;
		if (*argv == NULL)
			break ;
		argv++;
	}
	splitted_argv[sparg_i] = NULL;
	return (splitted_argv);
}
