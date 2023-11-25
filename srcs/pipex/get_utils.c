/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:14:49 by toshota           #+#    #+#             */
/*   Updated: 2023/11/25 17:34:31 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool	get_env_path(char ***env_path, char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", ft_strlen("PATH=")))
		i++;
	if (is_path_found(envp[i]) == false)
		return (false);
	*env_path = check_malloc(ft_split(envp[i] + ft_strlen("PATH="), ':'));
	add_slash_eos(env_path);
	return (true);
}

bool	get_pipe(t_pipex_data *pipex_data, int cmd_i)
{
	return (check_pipe(pipe(pipex_data->pipe_fd[cmd_i])));
}
