/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:39:21 by toshota           #+#    #+#             */
/*   Updated: 2023/12/20 17:10:02 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "expander.h"

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
	if (get_pipe_count(pipex->argv) == 0)
		ft_putstr_fd(EXIT_MSG, pipex->outfile_fd);
	if (cmd[1])
	{
		if (is_cmd_arg_num(cmd[1]) == false)
			return (put_error_w_cmd_filename \
			("exit", cmd[1], "numeric argument required", pipex), exit(2), false);
		if (get_exit_argc(cmd) > 2)
		{
			*pipex->error_num = 1;
			return (put_error("minishell: exit: too many arguments\n"), true);
		}
		if (get_cmd_absolute_path_count(pipex) == 1)
			exit((unsigned char)ft_atoi(cmd[1]));
		else
		{
			*pipex->error_num = (unsigned char)ft_atoi(cmd[1]);
			return (true);
		}
	}
	else if (get_cmd_absolute_path_count(pipex) == 1)
		exit(*pipex->error_num);
	return (true);
}
