/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 09:23:37 by toshota           #+#    #+#             */
/*   Updated: 2023/12/19 22:00:12 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static bool	is_argv_exist(char **argv)
{
	char	*argv_wo_space;

	if (ft_strlen(argv[0]) == 0)
		return (false);
	argv_wo_space = check_malloc(ft_strtrim(argv[0], " "));
	if (ft_strlen(argv_wo_space) == 0)
		return (free(argv_wo_space), false);
	return (free(argv_wo_space), true);
}

int	loop_pipex(t_tools *tools, t_env **env)
{
	char	***splitted_argv;
	char	**splitter;
	char	**h_envp;

	if (is_argv_exist(tools->tmp_array) == false)
		return (true);
	if (is_splitter_exist(tools->tmp_array) == false)
	{
		h_envp = node_to_array(*env);
		pipex(tools->tmp_array, h_envp, env, tools);
		all_free_tab(h_envp);
		return (tools->error_num);
	}
	get_loop_pipex(tools->tmp_array, &splitted_argv, &splitter);
	do_loop_pipex(splitted_argv, splitter, env, tools);
	return (end_loop_pipex(splitted_argv, splitter), tools->error_num);
}
