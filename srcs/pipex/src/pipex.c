/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 17:32:48 by toshota           #+#    #+#             */
/*   Updated: 2023/11/01 16:10:13 by toshota          ###   ########.fr       */
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
int	pipex(int argc, char **argv, char **envp)
{
	t_pipex_data	pipex_data;

	check_arg(argc, argv);
	get_pipex_data(argc, argv, envp, &pipex_data);
	do_pipe(envp, &pipex_data);
	end_pipex(argv, &pipex_data);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	pipex(argc, argv, envp);
	return (0);
}

// __attribute__((destructor)) static void destructor()
// {
// 	system("leaks -q pipex");
// }
