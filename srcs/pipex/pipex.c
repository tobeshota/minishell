/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 17:32:48 by toshota           #+#    #+#             */
/*   Updated: 2023/12/28 15:33:25 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "expander.h"

static int	is_true(int ret, t_pipex *pipex, t_tools *tools)
{
	(void)tools;
	if (ret == false)
	{
		if (*pipex->error_num == 0)
			*pipex->error_num = 1;
		if (g_in_cmd == SIG_INT_COMING)
			*pipex->error_num = 130;
		return (false);
	}
	else if (*pipex->error_num != 0)
		*pipex->error_num = 0;
	return (true);
}

int	pipex(char **argv, char **h_envp, t_env **env, t_tools *tools)
{
	t_pipex	pipex;

	if (is_true(get_pipex(argv, h_envp, &pipex, tools), &pipex, tools) == false)
		return (end_pipex(&pipex), false);
	if (is_true(do_pipex(h_envp, env, &pipex, tools), &pipex, tools) == false)
		return (end_pipex(&pipex), false);
	return (is_true(end_pipex(&pipex), &pipex, tools));
}
