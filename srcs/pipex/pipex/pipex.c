/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 17:32:48 by toshota           #+#    #+#             */
/*   Updated: 2023/12/29 13:15:09 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "expander.h"

static int	is_true(int ret, t_pipex *pipex)
{
	if (ret == false)
	{
		if (*pipex->error_num == 0)
			*pipex->error_num = 1;
		if (g_in_cmd == SIG_INT_COMING)
			*pipex->error_num = 130;
		return (false);
	}
	else if (ret != NOT_FOUND)
		*pipex->error_num = 0;
	return (ret);
}

int	pipex(char **argv, char **h_envp, t_env **env, t_tools *tools)
{
	t_pipex	pipex;
	int		ret;

	ret = is_true(get_pipex(argv, h_envp, &pipex, tools), &pipex);
	if (ret == NOT_FOUND)
		return (end_pipex(&pipex), true);
	if (ret == false)
		return (end_pipex(&pipex), false);
	if (is_true(do_pipex(h_envp, env, &pipex, tools), &pipex) == false)
		return (end_pipex(&pipex), false);
	return (is_true(end_pipex(&pipex), &pipex));
}
