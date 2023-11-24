/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:34:25 by toshota           #+#    #+#             */
/*   Updated: 2023/11/24 15:20:33 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	put_arg_for_debug(char **argv)
{
	int	i;

	i = -1;
	if (argv[0] != NULL)
		ft_printf("%ssplitted:%s ", BOLD, DEFAULT);
	while (argv[++i])
		ft_printf("\"%s\"\t", argv[i]);
	if (argv[0] != NULL)
		ft_printf("\n");
}

int	pipex_debug(int argc, char **argv, char **envp)
{
	int	i;

	i = 0;
	argv = (char **)malloc(INT_MAX);
	//
	argv[i++] = ft_strdup("cd ..");
	//
	argv[i] = NULL;
	pipex(argc, argv, &envp);
	all_free_tab(argv);
	return (0);
}

int	minishell(int argc, char **argv, char **envp)
{
	char	*line;

	while (true)
	{
		line = readline(MINISHELL_PROMPT);
		if (!line)
			break ;
		// 本来はft_splitでなくlexerとparser．いまは区切り文字','で分割している
		// 【入力例】ls -l,|,wc -l
		// 【入力例】cat infile,>,outfile
		argv = ft_split(line, ',');
		if (*line)
			add_history(line);
		put_arg_for_debug(argv);
		pipex(argc, argv, &envp);
		all_free_tab(argv);
		free(line);
	}
	ft_printf(EXIT_MSG);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	minishell(argc, argv, envp);
	// pipex_debug(argc, argv, envp);
}

__attribute__((destructor)) static void destructor()
{
	system("leaks -q minishell");
}
