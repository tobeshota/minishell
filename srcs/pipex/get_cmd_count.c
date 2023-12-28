/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_count.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 09:00:12 by toshota           #+#    #+#             */
/*   Updated: 2023/12/28 15:47:16 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

bool	is_arg_false(char *cunnret_argv, int ret, t_pipex *pipex)
{
	if (check_cmd_exist(cunnret_argv, ret, pipex) == false)
		return (false);
	if (check_is_dot(ret, pipex) == false)
		return (false);
	if (check_is_dir(cunnret_argv, ret, pipex) == false)
		return (false);
	return (true);
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
		if (is_arg_false(cunnret_argv, ret, pipex) == false)
			return (false);
		// check_cmd_exist(cunnret_argv, ret, pipex);
		// check_is_dot(ret, pipex);
		// check_is_dir(cunnret_argv, ret, pipex);
		arg_i++;
		free_tab(cunnret_argv);
		free_tab(prev_argv);
	}
	return (cmd_count);
}

int	get_cmd_count_wo_error_msg(t_pipex *pipex, char **h_envp)
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
		arg_i++;
		free_tab(cunnret_argv);
		free_tab(prev_argv);
	}
	return (cmd_count);
}

int	count_builtin(t_pipex *pipex)
{
	int	cmd_i;
	int	builtg_in_cmd_count;

	cmd_i = 0;
	builtg_in_cmd_count = 0;
	while (pipex->cmd_absolute_path[cmd_i])
	{
		if (is_cmd_builtin(pipex->cmd_absolute_path[cmd_i]))
			builtg_in_cmd_count++;
		cmd_i++;
	}
	return (builtg_in_cmd_count);
}
