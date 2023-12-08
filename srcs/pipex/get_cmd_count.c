/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_count.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 09:00:12 by toshota           #+#    #+#             */
/*   Updated: 2023/12/08 18:01:05 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	check_is_dir(char *filename, int ret)
{
	if (ret == IS_A_DIRECTORY)
	{
		put_error_w_cmd(filename, "is a directory");
		g_global.error_num = 126;
	}
}

static void	check_cmd_exist(char *filename, int ret)
{
	if (ret == NOT_FOUND)
	{
		put_error_w_cmd(filename, "command not found");
		g_global.error_num = 127;
	}
}

static void	check_is_dot(int ret)
{
	if (ret == IS_DOT)
	{
		put_error("minishell: .: filename argument required\n.\
		: usage: . filename [arguments]\n");
		g_global.error_num = 2;
	}
}

int	get_cmd_count(char **argv, char **heap_envp)
{
	int		cmd_count;
	int		arg_i;
	int		ret;
	char	*argv_wo_param;

	cmd_count = 0;
	arg_i = 0;
	while (argv[arg_i])
	{
		argv_wo_param = check_malloc \
		(ft_substr(argv[arg_i], 0, strlen_until_c(argv[arg_i], ' ')));
		ret = is_cmd(argv, arg_i, heap_envp);
		if (ret == true)
			cmd_count++;
		check_is_dot(ret);
		check_is_dir(argv_wo_param, ret);
		check_cmd_exist(argv_wo_param, ret);
		arg_i++;
		free(argv_wo_param);
	}
	return (cmd_count);
}
