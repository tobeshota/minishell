/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_count.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 09:00:12 by toshota           #+#    #+#             */
/*   Updated: 2023/12/16 10:59:53 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	get_index_upto_space(char *str)
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
	int		i_upto_space;
	int		ret;
	char	*argv_wo_param;

	cmd_count = 0;
	arg_i = 0;
	while (argv[arg_i])
	{
		i_upto_space = get_index_upto_space(argv[arg_i]);
		argv_wo_param = check_malloc(ft_substr(argv[arg_i], 0, \
		strlen_until_c(argv[arg_i] + i_upto_space, ' ') + i_upto_space));
		ret = is_cmd(argv, arg_i, h_envp);
		if (ret == true)
			cmd_count++;
		if (check_cmd_exist(argv_wo_param, ret) == false || \
		check_is_dot(ret) == false || check_is_dir(argv_wo_param, ret) == false)
			return (free(argv_wo_param), false);
		arg_i++;
		free(argv_wo_param);
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
