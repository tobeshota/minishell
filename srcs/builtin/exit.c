/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:39:21 by toshota           #+#    #+#             */
/*   Updated: 2023/11/25 22:40:18 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	get_cmd_argc(char **cmd)
{
	int	cmd_argc;

	cmd_argc = 0;
	while (cmd[cmd_argc])
		cmd_argc++;
	return (cmd_argc);
}

static bool	is_sign(int c)
{
	return (c == '+' || c == '-');
}

static bool	is_cmd_arg_num(char *cmd_arg)
{
	if (is_sign(*cmd_arg) && *(cmd_arg + 1))
		cmd_arg++;
	while (*cmd_arg && ft_strchr("0123456789", *cmd_arg))
		cmd_arg++;
	return (*cmd_arg == '\0');
}

static unsigned char	get_exit_return_value(char *cmd_arg)
{
	return ((unsigned char)ft_atoi(cmd_arg));
}

// https://itpfdoc.hitachi.co.jp/manuals/3020/30203S3530/JPAS0289.HTM
int	exec_exit(char **cmd, t_pipex *pipex)
{
	ft_putstr_fd(EXIT_MSG, pipex->outfile_fd);
	if (cmd[1])
	{
		if (get_cmd_argc(cmd) > 2)
			return (put_error("bash: exit: too many arguments\n"), false);
		if (is_cmd_arg_num(cmd[1]) == false)
		{
			put_error("bash: exit: ");
			put_error(cmd[1]);
			put_error(": numeric argument required\n");
			exit(1);
		}
		exit(get_exit_return_value(cmd[1]));
	}
	else
	{
		/* exitの引数を指定しなかった場合，最後に実行したコマンドの終了コードを戻り値としてシェルを終了する．これを実装する！ */
		// $?を展開する
		// $?をexit();関数の引数に入れてexitする
		exit(0);
	}
	return (true);
}
