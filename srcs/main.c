/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:34:25 by toshota           #+#    #+#             */
/*   Updated: 2023/11/18 19:37:40 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void put_arg_for_debug(char **argv)
{
	int i;

	i = -1;
	ft_printf("%ssplited:%s ", BOLD, DEFAULT);
	while(argv[++i])
		ft_printf("\"%s\"\t", argv[i]);
	if(argv[0] != NULL)
		ft_printf("\n");
}

int	main(int argc, char **argv, char **envp)
{
	char *input;

	input = readline(MINISHELL_PROMPT);
	while(input)
	{
		argv = ft_split(input, '"');	//	lexer + parser
		put_arg_for_debug(argv);
		pipex(argc, argv, envp);
		free(input);
		all_free_tab(argv);
		input = readline(MINISHELL_PROMPT);
	}
	ft_printf(EXIT_MSG);
	return (0);
}


__attribute__((destructor)) static void destructor()
{
	system("leaks -q minishell");
}
