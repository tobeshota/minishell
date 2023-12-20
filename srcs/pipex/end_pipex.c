/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:54:49 by toshota           #+#    #+#             */
/*   Updated: 2023/12/19 21:07:43 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	free_tab(char *ptr)
{
	free(ptr);
	ptr = NULL;
	return (0);
}

void	all_free_tab(char **ptr)
{
	int	i;

	i = 0;
	while (ptr && ptr[i])
	{
		free(ptr[i]);
		ptr[i] = NULL;
		i++;
	}
	free(ptr);
	ptr = NULL;
}

void	all_free_int(int **ptr)
{
	int	i;

	i = 0;
	while (ptr && ptr[i])
	{
		free(ptr[i]);
		ptr[i] = NULL;
		i++;
	}
	free(ptr);
	ptr = NULL;
}

bool	end_pipex(t_pipex *pipex)
{
	all_free_tab(pipex->argv);
	all_free_tab(pipex->cmd_absolute_path);
	all_free_tab(pipex->cmd_absolute_path_with_parameter);
	all_free_int(pipex->pipe_fd);
	if (close_fd(pipex) == false)
		return (rm_here_doc(), false);
	if (rm_here_doc() == false)
		return (false);
	return (true);
}
