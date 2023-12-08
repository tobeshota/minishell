/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 09:23:37 by toshota           #+#    #+#             */
/*   Updated: 2023/12/08 17:36:22 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// cat infile,|,cat,|,cat,|,cat,|,cat,;,echo -n wow,;,pwd
// pwd,&&,b.out,||,echo wow
// b.out,&&,echo success,||,echo failure
int	loop_pipex(char **argv, t_env **env)
{
	char	***splitted_argv;
	char	**splitter;
	char	**heap_envp;

	if (is_splitter_exist(argv) == false)
	{
		heap_envp = node_to_array(*env);
		pipex(argv, heap_envp, env);
		all_free_tab(heap_envp);
		return (g_global.error_num);
	}
	get_loop_pipex(argv, &splitted_argv, &splitter);
	do_loop_pipex(splitted_argv, splitter, env);
	return (end_loop_pipex(splitted_argv, splitter), g_global.error_num);
}
