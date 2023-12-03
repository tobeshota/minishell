/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 09:23:37 by toshota           #+#    #+#             */
/*   Updated: 2023/12/03 09:46:40 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	all_free_triple_tab(char ***ptr)
{
	int	i;

	i = 0;
	while (ptr && ptr[i])
	{
		all_free_tab(ptr[i]);
		i++;
	}
	free(ptr);
	ptr = NULL;
}

int get_splitter_count(char **argv)
{
	int splitter_count;
	int arg_i;

	splitter_count = 0;
	arg_i = 0;
	while(argv[arg_i])
	{
		if(is_match(argv[arg_i], ";") || is_match(argv[arg_i], "&&") || is_match(argv[arg_i], "||"))
			splitter_count++;
		arg_i++;
	}
ft_printf("splitter_count:\t%d\n", splitter_count);
	return splitter_count;
}

char ***get_splitted_argv(char **argv)
{
	char ***splited_argv;
	int splited_i;
	// splited_argの数ぶんmallocする
	splited_argv = (char ***)check_malloc(malloc(sizeof(char **) * (get_splitter_count(argv) + 1)));
	// それぞれのsplited_argvに入るargvの数を取得する
	// splited_i = 0;
	// while(splited_argv[splited_i])
	// それぞれのsplited_argvに入るargvの数ぶんmallocする
	// 各要素をft_strdup();で格納する
	return splited_argv;
}


int	loop_pipex(char **argv, t_env **env)
{
	char ***splitted_argv;
	// char **splitter;
	// int arg_i;
	int ret;

	//	argvを && || ; によって分割する
	splitted_argv = get_splitted_argv(argv);
	// // argvを分割する && || ; を取得する
	// splitter = get_splitter(argv);
	// // whileループで回していく

	ret = pipex(argv, env);
	return all_free_triple_tab(splitted_argv), ret;
}
