/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 09:23:37 by toshota           #+#    #+#             */
/*   Updated: 2023/12/04 11:04:17 by toshota          ###   ########.fr       */
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

int is_specified_splitter(char *str)
{
	return (is_match(str, ";") || is_match(str, "&&") || is_match(str, "||"));
}

int get_splitter_count(char **argv)
{
	int splitter_count;
	int arg_i;

	splitter_count = 0;
	arg_i = 0;
	while(argv[arg_i])
	{
		if (is_specified_splitter(argv[arg_i]))
			splitter_count++;
		arg_i++;
	}
// ft_printf("splitter_count:\t%d\n", splitter_count);
	return splitter_count;
}

int get_splitted_argc(char **argv)
{
	int arg_i;

	arg_i = 0;
	while(argv[arg_i])
		arg_i++;
	if (is_specified_splitter(argv[arg_i-1]))
		return get_splitter_count(argv);
	else
		return get_splitter_count(argv) + 1;
}

// ls -a ; ps
int get_argc(char **argv, int splitted_i)
{
	int argc;
	int splitter_count;

	argc = 0;
	splitter_count = 0;
	// splitted_iの数だけsplitterを見送る
	while(true)
	{
		if (is_specified_splitter(argv[argc]))
			splitter_count++;
		if (splitter_count >= splitted_i)
			break;
		argc++;
	}
	return argc;
}

static void malloc_splitted_argv_double_ptr(char ***splitted_argv, char **argv)
{
	int sparg_i;
	int arg_i;

	sparg_i = 0;
	while(true)
	{
		arg_i = 0;
		while (argv[arg_i] && is_specified_splitter(argv[arg_i]) == false)
			arg_i++;
		if (argv[arg_i] == NULL && is_specified_splitter(argv[arg_i-1]) == true)
			break;
		splitted_argv[sparg_i++] = (char **)check_malloc(malloc((sizeof(char *) * (arg_i + 1))));
		if (argv[arg_i] == NULL)
			break;
		argv += arg_i + 1;
	}
}

char **get_splitter(char **argv)
{
	char **splitter;
	int sp_i;

	splitter = (char **)check_malloc(malloc(sizeof(char *) * (get_splitter_count(argv) + 1)));
	sp_i = 0;
	while(*argv)
	{
		if(is_specified_splitter(*argv))
			splitter[sp_i++] = check_malloc(ft_strdup(*argv));
		argv++;
	}
	splitter[sp_i] = NULL;
	return splitter;
}

char ***get_splitted_argv(char **argv)
{
	char ***splitted_argv;
	int sparg_i;
	int element_i;

	// splited_argの数ぶんmallocする
	splitted_argv = (char ***)check_malloc(malloc(sizeof(char **) * (get_splitted_argc(argv) + 1)));
	// それぞれのsplited_argvに入るargvの数ぶんmallocする
	malloc_splitted_argv_double_ptr(splitted_argv, argv);
	// 各要素をft_strdup();で格納する
	sparg_i = 0;
	while(*argv)
	{
		element_i = 0;
		while(*argv && is_specified_splitter(*argv) == false)
			splitted_argv[sparg_i][element_i++] = check_malloc(ft_strdup(*argv++));
		splitted_argv[sparg_i++][element_i] = NULL;
		if (*argv == NULL)
			break;
		argv++;
	}
	splitted_argv[sparg_i] = NULL;
	return splitted_argv;
}


void put_triple_tab_for_debug(char ***tab)
{
	int i;
	int j;

	i = 0;
	while(tab && tab[i])
	{
		j = 0;
		while(tab && tab[i][j])
		{
			ft_printf("\"%s\"\t", tab[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

void put_double_tab_for_debug(char **tab)
{
	int i;

	i = 0;
	while(tab[i])
	{
		ft_printf("\"%s\"\t", tab[i]);
		i++;
	}
	ft_printf("\n");
}

bool is_splitter_exist(char **argv)
{
	int arg_i;

	arg_i = 0;
	while(argv[arg_i])
	{
		if (is_specified_splitter(argv[arg_i]) == true)
			return true;
		arg_i++;
	}
	return false;
}

// cat infile,|,cat,|,cat,|,cat,|,cat,;,echo -n wow,;,pwd
int	loop_pipex(char **argv, t_env **env)
{
	char ***splitted_argv;
	char **splitter;
	int sparg_i;
	int spl_i;
	int ret;

	// そもそも区切り文字がargvにない場合はそのままpipexを実行する！
	if (is_splitter_exist(argv) == false)
		return pipex(argv, env);

	//	argvを && || ; によって分割する
	splitted_argv = get_splitted_argv(argv);
// ft_printf("\n\nsplitted_argv:\t");
// put_triple_tab_for_debug(splitted_argv);

	// argvを分割する && || ; を取得する
	splitter = get_splitter(argv);
// ft_printf("splitter:\t");
// put_double_tab_for_debug(splitter);

	// whileループで回していく
	sparg_i = -1;
	spl_i = 0;
	while(splitted_argv[++sparg_i])
	{
		ret = pipex(splitted_argv[sparg_i], env);
		if(is_match(splitter[spl_i], ";"))
			continue;
	}


all_free_triple_tab(splitted_argv);
all_free_tab(splitter);
return true;

	// ret = pipex(argv, env);
	// return all_free_triple_tab(splitted_argv), all_free_tab(splitter), ret;
// return pipex(argv, env);
}
