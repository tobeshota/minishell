/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:14:49 by toshota           #+#    #+#             */
/*   Updated: 2023/11/18 15:17:16 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_env_path(char ***env_path, char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", ft_strlen("PATH=")))
		i++;
	if (is_path_found(envp[i]) == FALSE)
		return FALSE;
	*env_path = check_malloc(ft_split(envp[i] + ft_strlen("PATH="), ':'));
	add_slash_eos(env_path);
	return TRUE;
}

int	get_pwd(char ***pwd_path, char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PWD=", ft_strlen("PWD=")))
		i++;
	if(is_path_found(envp[i]) == FALSE)
		return FALSE;
	*pwd_path = check_malloc(ft_split(envp[i] + ft_strlen("PWD="), ':'));
	add_slash_eos(pwd_path);
	return TRUE;
}

int	get_down_count_from_pwd(char *relative_path)
{
	int	down_count_from_pwd;

	down_count_from_pwd = 0;
	while (ft_strnstr(relative_path, "../", ft_strlen(relative_path)))
	{
		down_count_from_pwd++;
		relative_path += ft_strlen("../");
	}
	return (down_count_from_pwd);
}

char	*get_pwd_for_relative_path(char ***pwd_path, int down_count_from_pwd)
{
	int	delete_len;
	char *pwd_for_relative_path;

	if (ft_strrnchr(pwd_path[0][0], '/', down_count_from_pwd) == NULL)
		delete_len = 0;
	else
		delete_len = ft_strlen(ft_strrnchr(pwd_path[0][0], '/',
					down_count_from_pwd) + 1);
	pwd_for_relative_path = check_malloc(ft_substr(pwd_path[0][0], 0, ft_strlen(pwd_path[0][0]) - delete_len));
	return pwd_for_relative_path;
}

int	get_pipe(t_pipex_data *pipex_data, int cmd_i)
{
	if(is_pipe_successfully(pipe(pipex_data->pipe_fd[cmd_i])) == FALSE)
		return FALSE;
	return TRUE;
}
