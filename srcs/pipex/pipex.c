/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 17:32:48 by toshota           #+#    #+#             */
/*   Updated: 2023/12/18 12:01:32 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	is_true(int ret, t_pipex *pipex)
{
	if (ret == false)
	{
		if (*pipex->error_num == 0)
			*pipex->error_num = 1;
		return (false);
	}
	return (true);
}

int	pipex(char **argv, char **h_envp, t_env **env, t_tools *tools)
{
	t_pipex	pipex;

	if (is_true(get_pipex(argv, h_envp, &pipex, tools), &pipex) == false)
		return (end_pipex(&pipex), false);
	if (is_true(do_pipex(h_envp, env, &pipex, tools), &pipex) == false)
		return (end_pipex(&pipex), false);
	return (is_true(end_pipex(&pipex), &pipex));
}
