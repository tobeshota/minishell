/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:34:25 by toshota           #+#    #+#             */
/*   Updated: 2023/11/18 15:18:46 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	ft_printf("%sminishell >%s ", GREEN, DEFAULT);
// argv = ft_split("< infile cat | cat | cat | sort >> outfile", ' ');
argv = ft_split(">> outfile < infile2 cat < infile | cat < infile2 >> outfile2", ' ');

	// lexer
	// parser
	pipex(argc, argv, envp);
	all_free_tab(argv);
	return (0);
}

__attribute__((destructor)) static void destructor()
{
	system("leaks -q minishell");
}
