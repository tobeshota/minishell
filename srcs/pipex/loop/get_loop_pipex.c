/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_loop_pipex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 12:36:04 by toshota           #+#    #+#             */
/*   Updated: 2023/12/04 12:36:12 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	get_loop_pipex(char **argv, char ****splitted_argv, char ***splitter)
{
	*splitted_argv = get_splitted_argv(argv);
	*splitter = get_splitter(argv);
}
