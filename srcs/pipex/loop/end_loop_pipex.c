/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_loop_pipex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 12:34:35 by toshota           #+#    #+#             */
/*   Updated: 2023/12/04 12:47:27 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	all_free_triple_tab(char ***ptr)
{
	int	i;

	i = 0;
	while (ptr && ptr[i])
	{
		all_free_tab(ptr[i]);
		i++;
	}
	free(ptr);
	ptr = NULL;
}

void	end_loop_pipex(char ***splitted_argv, char **splitter)
{
	all_free_triple_tab(splitted_argv);
	all_free_tab(splitter);
}
