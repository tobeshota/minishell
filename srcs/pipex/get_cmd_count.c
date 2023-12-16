/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_count.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 09:00:12 by toshota           #+#    #+#             */
/*   Updated: 2023/12/16 19:50:27 by toshota          ###   ########.fr       */
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

int	get_cmd_count(char **argv, char **h_envp)
{
	int		cmd_count;
	int		arg_i;
	int		ret;
	char	**cmd_array;

	cmd_count = 0;
	arg_i = 0;
	while (argv[arg_i])
	{
		cmd_array = split_wo_enclosed_str(argv[arg_i], ' ');
		ret = is_cmd(cmd_array, 0, h_envp);
		if (ret == true)
			cmd_count++;
		if (check_cmd_exist(cmd_array[0], ret) == false || \
		check_is_dot(ret) == false || check_is_dir(cmd_array[0], ret) == false)
			return (all_free_tab(cmd_array), false);
		arg_i++;
		all_free_tab(cmd_array);
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
