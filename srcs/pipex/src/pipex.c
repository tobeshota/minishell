/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 17:32:48 by toshota           #+#    #+#             */
/*   Updated: 2023/10/31 15:29:39 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pipex(int argc, char **argv, char **envp)
{
	t_pipex_data	pipex_data;

	check_arg(argc, argv);
	get_pipex_data(argc, argv, envp, &pipex_data);
	do_pipe(envp, &pipex_data);
	end_pipex(argv, &pipex_data);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	pipex(argc, argv, envp);
	return (0);
}

// __attribute__((destructor)) static void destructor()
// {
// 	system("leaks -q pipex");
// }
