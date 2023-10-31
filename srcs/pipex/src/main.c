/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 17:32:48 by toshota           #+#    #+#             */
/*   Updated: 2023/10/31 15:22:56 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex_data	pipex_data;

	check_arg(argc, argv);
	get_pipex_data(argc, argv, envp, &pipex_data);
	pipex(envp, &pipex_data);
	end_pipex(argv, &pipex_data);
}

// __attribute__((destructor)) static void destructor()
// {
// 	system("leaks -q pipex");
// }
