/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:34:25 by toshota           #+#    #+#             */
/*   Updated: 2023/11/18 18:26:04 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void put_arg(char **argv)
// {
// 	int i;

// 	i = -1;
// 	while(argv[++i])
// 		ft_printf("[%s]", argv[i]);
// 	ft_printf("\n");
// }

// int main(int argc, char **argv, char **envp)
// {
// 	argv = ft_split("> outfile", ' ');
// 	pipex(argc, argv, envp);
// 	all_free_tab(argv);
// }

// > outfile >> outfile2を実装する！
int	main(int argc, char **argv, char **envp)
{
	char *input;

	input = readline(MINISHELL_PROMPT);
	while(input)
	{
		argv = ft_split(input, ' ');
		// lexer
		// parser
		// >> outfile < infile2 cat | cat < infile2 >> outfile2
		// put_arg(argv);
		pipex(argc, argv, envp);
		free(input);
		all_free_tab(argv);
		input = readline(MINISHELL_PROMPT);
	}
	ft_printf("exit");
	return (0);
}


__attribute__((destructor)) static void destructor()
{
	system("leaks -q minishell");
}
