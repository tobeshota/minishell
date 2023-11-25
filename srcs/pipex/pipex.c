/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 17:32:48 by toshota           #+#    #+#             */
/*   Updated: 2023/11/25 19:30:08 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// 引数として，「変数展開された」，「コマンドとオプションが一つにまとまった(by parser)」文字列がくる
// 文字列の中には「｜」や「<<」，「>>」が入ることもある
// 最後の文字列が「>>」であるとき，outfileを追記モードで開く
// 最初の文字列が「<<」であるとき，infileを追記も
/*

■終了ステータス
【1】異常終了
・存在しない入力ファイルを渡された
・open()，close()，read()，fork()，dup()，execve()，unlink()，wait()に失敗した
【0】正常終了

*/
int	pipex(char **argv, char ***envp, t_env **env_node)
{
	t_pipex_data	pipex_data;

	if (get_pipex_data(argv, &pipex_data) == false)
		return (end_pipex(&pipex_data), 1);
	if (do_pipe(envp, &pipex_data, argv) == false)
		return (end_pipex(&pipex_data), 1);
	if (end_pipex(&pipex_data) == false)
		return (1);
	return (0);
}

// > outfile ls | echo Hello
// > は次の｜が来るまでの出力先を指定している
/* 入出力先が指定される範囲は次の｜が来るまでである．

>> outfile < infile cat | cat < infile2 >> outfile2
出力先の優先順位は ">>" == ">" > "|"である．">>"や">"と"｜"の両方が出力先として指定されたとき，">>"や">"が優先される．

>> outfile < infile cat | cat >> outfile2
*/

/*
int	main(int argc, char **argv, char **envp)
{
argv = ft_split("< infile cat | cat | cat | sort >> outfile", ' ');

// int i = 0;
// argv = (char **)malloc(sizeof(char *) * 200);

// argv[i++] = ft_strdup("echo infile");

// < infile sort | cat infile2 >> outfile
// argv[i++] = ft_strdup("<");
// argv[i++] = ft_strdup("infile");
// argv[i++] = ft_strdup("sort");
// argv[i++] = ft_strdup("|");
// argv[i++] = ft_strdup("cat infile2");
// argv[i++] = ft_strdup(">>");
// argv[i++] = ft_strdup("outfile");

// > outfile ls | echo Hello
// argv[i++] = ft_strdup(">");
// argv[i++] = ft_strdup("outfile");
// argv[i++] = ft_strdup("ls");
// argv[i++] = ft_strdup("|");
// argv[i++] = ft_strdup("echo Hello");

// ls -la > outfile | cat infile
// argv[i++] = ft_strdup("ls -la");
// argv[i++] = ft_strdup(">");
// argv[i++] = ft_strdup("outfile");
// argv[i++] = ft_strdup("|");
// argv[i++] = ft_strdup("cat infile");

// << EOF cat -n > outfile
// argv[i++] = ft_strdup("<<");
// argv[i++] = ft_strdup("EOF");
// argv[i++] = ft_strdup("cat -n");
// argv[i++] = ft_strdup(">");
// argv[i++] = ft_strdup("outfile");

// cat infile << EOF > outfile
// argv[i++] = ft_strdup("cat infile");
// argv[i++] = ft_strdup("<<");
// argv[i++] = ft_strdup("EOF");
// argv[i++] = ft_strdup(">");
// argv[i++] = ft_strdup("outfile");

// >> outfile < infile2 cat infile | cat -n < infile2 >> outfile2
// argv[i++] = ft_strdup(">>");
// argv[i++] = ft_strdup("outfile");
// argv[i++] = ft_strdup("<");
// argv[i++] = ft_strdup("infile2");
// argv[i++] = ft_strdup("cat infile");
// argv[i++] = ft_strdup("|");
// argv[i++] = ft_strdup("cat -n");
// argv[i++] = ft_strdup("<");
// argv[i++] = ft_strdup("infile2");
// argv[i++] = ft_strdup(">>");
// argv[i++] = ft_strdup("outfile2");

// argv[i] = NULL;
pipex(argc, argv, envp);
all_free_tab(argv);
	return (0);
}*/

// __attribute__((destructor)) static void destructor()
// {
// 	system("leaks -q pipex");
// }
