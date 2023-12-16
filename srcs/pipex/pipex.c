/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 17:32:48 by toshota           #+#    #+#             */
/*   Updated: 2023/12/16 21:39:08 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	is_true(int ret)
{
	if (ret == false)
	{
		if (g_global.error_num == 0)
			g_global.error_num = 1;
		return (false);
	}
	return (true);
}

int	pipex(char **argv, char **h_envp, t_env **env, t_tools *tools)
{
	t_pipex	pipex;

	// pipex.error_num = &(tools->error_num);

	if (is_true(get_pipex(argv, h_envp, &pipex, tools)) == false)
		return (end_pipex(&pipex), false);
	if (is_true(do_pipex(h_envp, env, &pipex)) == false)
		return (end_pipex(&pipex), false);
	return (is_true(end_pipex(&pipex)));
}
