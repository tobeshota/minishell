/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 09:23:37 by toshota           #+#    #+#             */
/*   Updated: 2023/12/05 09:50:17 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// cat infile,|,cat,|,cat,|,cat,|,cat,;,echo -n wow,;,pwd
// pwd,&&,b.out,||,echo wow
int	loop_pipex(char **argv, char **envp, t_env **env)
{
	char	***splitted_argv;
	char	**splitter;
	int		ret;

	if (is_splitter_exist(argv) == false)
	{
		ret = pipex(argv, env);
		return (node_to_array(*env, &envp), ret);
	}
	get_loop_pipex(argv, &splitted_argv, &splitter);
	ret = do_loop_pipex(splitted_argv, splitter, envp, env);
	return (end_loop_pipex(splitted_argv, splitter), ret);
}
