/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 09:23:37 by toshota           #+#    #+#             */
/*   Updated: 2023/12/16 21:47:01 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// cat infile,|,cat,|,cat,|,cat,|,cat,;,echo -n wow,;,pwd
// pwd,&&,b.out,||,echo wow
// b.out,&&,echo success,||,echo failure
int	loop_pipex(t_tools *tools, t_env **env)
{
	char	***splitted_argv;
	char	**splitter;
	char	**h_envp;

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
