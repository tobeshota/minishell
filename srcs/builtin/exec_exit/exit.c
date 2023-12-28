/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:39:21 by toshota           #+#    #+#             */
/*   Updated: 2023/12/28 15:51:14 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "expander.h"
#define OVERFLOW_ULL -42

static int	get_exit_argc(char **cmd)
{
	int	cmd_argc;

	cmd_argc = 0;
	while (cmd[cmd_argc])
		cmd_argc++;
	return (cmd_argc);
}

static bool	check_exit_argc_is_more_than_2(char **cmd, t_pipex *pipex,
		char *cmd_arg)
{
	if (get_exit_argc(cmd) > 2)
	{
		*pipex->error_num = 1;
		put_error("minishell: exit: too many arguments\n");
		free(cmd_arg);
	}
	return (false);
}

static bool	is_cmd_arg_num(char *cmd_arg)
{
	int					i;
	int					sign;
	unsigned long long	abs_ull;
	unsigned long long	abs_llong_min;

	if (is_argv_exist(&cmd_arg) == false)
		return (false);
	i = 0;
	if ((cmd_arg[i] == '+' || cmd_arg[i] == '-') && cmd_arg[i + 1])
		i++;
	while (cmd_arg[i] && ft_strchr("0123456789", cmd_arg[i]))
		i++;
	if (cmd_arg[i] != '\0')
		return (false);
	abs_ull = ascii_to_abs_ull(cmd_arg, &sign);
	if (sign == OVERFLOW_ULL)
		return (false);
	abs_llong_min = LLONG_MAX;
	abs_llong_min += 1;
	if (sign == -1)
		return (abs_ull <= abs_llong_min);
	else
		return (abs_ull <= LLONG_MAX);
}

static void	check_is_cmd_arg_num(bool ret, char *cmd_arg, t_pipex *pipex)
{
	if (ret == false)
	{
		put_error_w_cmd_filename \
		("exit", cmd_arg, "numeric argument required", pipex);
		free(cmd_arg);
		exit(2);
	}
}

int	exec_exit(char **cmd, t_pipex *pipex)
{
	char	*cmd_arg;

	cmd_arg = NULL;
	if (count_pipe(pipex->argv) == 0)
		ft_putstr_fd(EXIT_MSG, STDIN_FILENO);
	check_is_double_hyphen(cmd, pipex);
	if (cmd[1])
	{
		cmd_arg = omit_str(cmd[1], "\'\" ");
		check_is_cmd_arg_num(is_cmd_arg_num(cmd_arg), cmd_arg, pipex);
		if (check_exit_argc_is_more_than_2(cmd, pipex, cmd_arg) == true)
			return (true);
		if (get_cmd_absolute_path_count(pipex) == 1)
			exit((unsigned char)ft_atoi(cmd_arg));
		*pipex->error_num = (unsigned char)ft_atoi(cmd[1]);
		return (free(cmd_arg), true);
	}
	else if (get_cmd_absolute_path_count(pipex) == 1)
		exit(*pipex->error_num);
	return (free(cmd_arg), true);
}
