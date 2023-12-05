/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_loop_pipex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 12:49:44 by toshota           #+#    #+#             */
/*   Updated: 2023/12/05 11:46:07 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	is_continue(char **splitter, int spl_i, int ret)
{
	return (is_match(splitter[spl_i], ";") \
	|| (is_match(splitter[spl_i], "&&") && ret == true) \
	|| (is_match(splitter[spl_i], "||") && ret != true));
}

int	do_loop_pipex(char ***splitted_argv, char **splitter, char **envp,
		t_env **env)
{
	int	sparg_i;
	int	spl_i;
	int	ret;

	sparg_i = -1;
	spl_i = 0;
	while (splitted_argv[++sparg_i])
	{
		node_to_array(*env, &envp);
		ret = pipex(splitted_argv[sparg_i], env);
		if (splitter[spl_i] == NULL)
			break ;
		if (is_continue(splitter, spl_i, ret) && ++spl_i)
			continue ;
		else if (is_match(splitter[spl_i], "&&") && ret != true)
			while (is_match(splitter[spl_i], "&&") && ++sparg_i)
				spl_i++;
		else if (is_match(splitter[spl_i], "||") && ret == true)
			while (is_match(splitter[spl_i], "||") && ++sparg_i)
				spl_i++;
	}
	return (ret);
}
