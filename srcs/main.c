/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:34:25 by toshota           #+#    #+#             */
/*   Updated: 2023/11/25 20:59:42 by toshota          ###   ########.fr       */
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

int	minishell(char **argv, char **envp)
{
	char	*line;
	t_env	*env_node;

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
		env_node = array_to_node(envp);
		pipex(argv, &envp, &env_node);
		all_free_tab(argv);
		node_to_array(env_node, &envp);
		free(line);
		ft_nodeclear(&env_node);
	}
	ft_printf(EXIT_MSG);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc == 1 || argc != 1)
		minishell(argv, envp);
}

__attribute__((destructor)) static void destructor()
{
	system("leaks -q minishell");
}
