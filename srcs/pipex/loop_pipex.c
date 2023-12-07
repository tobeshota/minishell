/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 09:23:37 by toshota           #+#    #+#             */
/*   Updated: 2023/12/07 13:38:02 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// cat infile,|,cat,|,cat,|,cat,|,cat,;,echo -n wow,;,pwd
// pwd,&&,b.out,||,echo wow
// b.out,&&,echo success,||,echo failure
int	loop_pipex(char **argv, char **envp, t_env **env)
{
	char	***splitted_argv;
	char	**splitter;

	if (is_splitter_exist(argv) == false)
	{
		pipex(argv, env);
		return (node_to_array(*env, &envp), g_global.error_num);
	}
	get_loop_pipex(argv, &splitted_argv, &splitter);
	do_loop_pipex(splitted_argv, splitter, envp, env);
	return (end_loop_pipex(splitted_argv, splitter), g_global.error_num);
}
