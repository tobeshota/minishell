/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_loop_pipex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 12:49:44 by toshota           #+#    #+#             */
/*   Updated: 2023/12/04 12:52:39 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	do_loop_pipex(char ***splitted_argv, char **splitter, t_env **env)
{
	int	sparg_i;
	int	spl_i;
	int	ret;

	sparg_i = -1;
	spl_i = 0;
	while (splitted_argv[++sparg_i])
	{
		ret = pipex(splitted_argv[sparg_i], env);
		if (splitter[spl_i] == NULL)
			break ;
		if ((is_match(splitter[spl_i], ";") || (is_match(splitter[spl_i], "&&")
					&& ret == true) || (is_match(splitter[spl_i], "||")
					&& ret != true)) && ++spl_i)
			continue ;
		else if (is_match(splitter[spl_i], "&&"))
			while (is_match(splitter[spl_i], ";") == false
				&& is_match(splitter[spl_i], "||") == false && ++sparg_i)
				spl_i++;
		else if (is_match(splitter[spl_i], "||"))
			while (is_match(splitter[spl_i], ";") == false
				&& is_match(splitter[spl_i], "&&") == false && ++sparg_i)
				spl_i++;
	}
	return (ret);
}
