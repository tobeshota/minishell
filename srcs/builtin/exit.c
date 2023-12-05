/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:39:21 by toshota           #+#    #+#             */
/*   Updated: 2023/12/05 16:16:55 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	get_exit_argc(char **cmd)
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

int	exec_exit(char **cmd, t_pipex *pipex)
{
	if (get_cmd_absolute_path_count(pipex) != 1)
		return (true);
	ft_putstr_fd(EXIT_MSG, pipex->outfile_fd);
	if (cmd[1])
	{
		if (get_exit_argc(cmd) > 2)
			return (put_error("bash: exit: too many arguments\n"), false);
		if (is_cmd_arg_num(cmd[1]) == false)
		{
			put_error("minishell: exit: ");
			put_error(cmd[1]);
			put_error(": numeric argument required\n");
			exit(255);
		}
		exit((unsigned char)ft_atoi(cmd[1]));
	}
	else
		exit(g_global.error_num);
	return (true);
}
