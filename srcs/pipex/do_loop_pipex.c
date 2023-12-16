/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_loop_pipex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 12:49:44 by toshota           #+#    #+#             */
/*   Updated: 2023/12/16 21:53:19 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	is_continue(char **splitter, int spl_i, int ret)
{
	return (is_match(splitter[spl_i], ";") || (is_match(splitter[spl_i], "&&")
			&& ret == 0) || (is_match(splitter[spl_i], "||") && ret != 0));
}

static int	is_loop_in_and_operater(char **splitter, int spl_i, t_tools *tools)
{
	return (is_match(splitter[spl_i], "&&") && tools->error_num != 0);
}

static int	is_loop_in_or_operater(char **splitter, int spl_i, t_tools *tools)
{
	return (is_match(splitter[spl_i], "||") && tools->error_num == 0);
}

static void	increment(char **splitter, int *sparg_i, int *spl_i, t_tools *tools)
{
	while (is_loop_in_and_operater(splitter, *spl_i, tools))
	{
		(*sparg_i)++;
		(*spl_i)++;
	}
	while (is_loop_in_or_operater(splitter, *spl_i, tools))
	{
		(*sparg_i)++;
		(*spl_i)++;
	}
}

int	do_loop_pipex(char ***splitted_argv, char **splitter, t_env **env,
		t_tools *tools)
{
	int		sparg_i;
	int		spl_i;
	int		ret;
	char	**h_envp;

	sparg_i = 0;
	spl_i = 0;
	while (splitted_argv[sparg_i])
	{
		tools->error_num = 0;
		h_envp = node_to_array(*env);
		ret = pipex(splitted_argv[sparg_i], h_envp, env, tools);
		all_free_tab(h_envp);
		if (splitter[spl_i] == NULL)
			break ;
		if (is_continue(splitter, spl_i, tools->error_num) && ++spl_i
			&& ++sparg_i)
			continue ;
		increment(splitter, &sparg_i, &spl_i, tools);
		if (splitted_argv[sparg_i] == NULL)
			break ;
		sparg_i++;
	}
	return (ret);
}
