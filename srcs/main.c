/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:34:25 by toshota           #+#    #+#             */
/*   Updated: 2023/11/27 16:14:19 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	put_arg_for_debug(char **argv)
{
	int	i;

	i = -1;
	if (argv[0] != NULL)
		ft_printf("splitted: ");
	while (argv[++i])
		ft_printf("\"%s\"\t", argv[i]);
	if (argv[0] != NULL)
		ft_printf("\n");
}

void put_node_for_debug(t_env *node)
{
	while(node->next)
	{
		ft_printf("%5d\t%s\n", node->order, node->content);
		ft_nodenext(&node);
	}
	ft_printf("%5d\t%s\n", node->order, node->content);
	ft_nodefirst(&node);
}

void init_minishell(char **envp, t_env	**env)
{
	*env = array_to_node(envp);
	get_order(*env);
}

int	minishell(char **argv, char **envp)
{
	char	*line;
	t_env	*env;

	init_minishell(envp, &env);
	put_node_for_debug(env);
	while (true)
	{
		line = readline(MINISHELL_PROMPT);
		if (!line)
			break ;
		argv = ft_split(line, ',');	/* 本来はft_splitでなくlexerとparser．いまは区切り文字','で分割している */
		if (*line)
			add_history(line);
		put_arg_for_debug(argv);
		if(is_match(line, "putnode"))
			put_node_for_debug(env);
		else
			pipex(argv, &env);
		all_free_tab(argv);
		node_to_array(env, &envp);
		free(line);
	}
	ft_nodeclear(&env);
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
