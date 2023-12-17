/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_count.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 09:00:12 by toshota           #+#    #+#             */
/*   Updated: 2023/12/17 15:42:43 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	increment_upto_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	return (i);
}

void	get_argv_wo_param(char **argv, int arg_i, char **cunnret_argv,
		char **prev_argv)
{
	char	**cmd_array;

	cmd_array = split_wo_enclosed_str(argv[arg_i], ' ');
	*cunnret_argv = check_malloc(ft_strdup(cmd_array[0]));
	all_free_tab(cmd_array);
	if (arg_i > 0)
	{
		cmd_array = split_wo_enclosed_str(argv[arg_i - 1], ' ');
		*prev_argv = check_malloc(ft_strdup(cmd_array[0]));
		all_free_tab(cmd_array);
	}
	else
	{
		*prev_argv = NULL;
	}
}

int	get_cmd_count(t_pipex *pipex, char **h_envp)
{
	int		cmd_count;
	int		arg_i;
	int		ret;
	char	*cunnret_argv;
	char	*prev_argv;

	cmd_count = 0;
	arg_i = 0;
	while (pipex->argv[arg_i])
	{
		get_argv_wo_param(pipex->argv, arg_i, &cunnret_argv, &prev_argv);
		ret = is_cmd(cunnret_argv, prev_argv, h_envp);
		if (ret == true)
			cmd_count++;
		if (check_cmd_exist(cunnret_argv, ret, pipex) == false ||
			check_is_dot(ret, pipex) == false || \
			check_is_dir(cunnret_argv, ret, pipex) == false)
			return (free_tab(cunnret_argv), free_tab(prev_argv), false);
		arg_i++;
		free_tab(cunnret_argv);
		free_tab(prev_argv);
	}
	return (cmd_count);
}

int	get_builtin_cmd_count(t_pipex *pipex)
{
	int	cmd_i;
	int	builtin_cmd_count;

	cmd_i = 0;
	builtin_cmd_count = 0;
	while (pipex->cmd_absolute_path[cmd_i])
	{
		if (is_cmd_builtin(pipex->cmd_absolute_path[cmd_i]))
			builtin_cmd_count++;
		cmd_i++;
	}
	return (builtin_cmd_count);
}
