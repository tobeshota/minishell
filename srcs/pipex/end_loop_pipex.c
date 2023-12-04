/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_loop_pipex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 12:34:35 by toshota           #+#    #+#             */
/*   Updated: 2023/12/04 12:34:39 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	end_loop_pipex(char ***splitted_argv, char **splitter)
{
	all_free_triple_tab(splitted_argv);
	all_free_tab(splitter);
}
