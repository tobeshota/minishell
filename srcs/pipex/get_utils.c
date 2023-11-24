/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:14:49 by toshota           #+#    #+#             */
/*   Updated: 2023/11/24 12:44:24 by toshota          ###   ########.fr       */
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

bool	get_pwd(char ***pwd_path, char **envp)
{
	int env_i;

	env_i = 0;
	while (envp[env_i] && ft_strncmp(envp[env_i], "PWD=", ft_strlen("PWD=")))
		env_i++;
	if (is_path_found(envp[env_i]) == false)
		return (false);
	*pwd_path = check_malloc(ft_split(envp[env_i] + ft_strlen("PWD="), ':'));
	add_slash_eos(pwd_path);
	return (true);
}

// int	get_down_count_from_cwd(char *relative_path)
// {
// 	int	down_count_from_pwd;

// 	down_count_from_pwd = 0;
// 	while (ft_strnstr(relative_path, "../", ft_strlen(relative_path)))
// 	{
// 		down_count_from_pwd++;
// 		relative_path += ft_strlen("../");
// 	}
// 	// 最後だけ..が考えられる cd ..
// 	if (ft_strnstr(relative_path, "..", ft_strlen("..")))
// 	{
// 		down_count_from_pwd++;
// 		relative_path += ft_strlen("..");
// 	}
// 	return (down_count_from_pwd);
// }

// 引数として渡ってくる**pwd_path: "/Users/tobeshota/workspace/42/minishell/"
// char	*down_cwd(char *cwd, int down_count_from_cwd)
// {
// 	int		delete_len_for_cwd;

// 	while(down_count_from_cwd)
// 	{
// 		if (!ft_strncmp(cwd, "PWD=/", ft_strlen(cwd)))
// 			break;
// 		else
// 		{
// 			delete_len_for_cwd = ft_strlen(cwd) - ft_strlen(ft_strrchr(cwd, '/'));
// 			ft_strlcpy(cwd, cwd, delete_len_for_cwd+1);
// 		}
// 		down_count_from_cwd--;
// 	}
// 	return cwd;
// }

// char	*down_passed_path(char *passed_path, int down_count_from_cwd)
// {
// 	int	delete_len_for_passed_path_ptr;

// 	while(down_count_from_cwd)
// 	{
// 		if (!ft_strncmp(passed_path, "..", ft_strlen(passed_path)))
// 		{
// 			ft_strlcpy(passed_path, "", 1);
// 		}
// 		else
// 		{
// 			delete_len_for_passed_path_ptr = ft_strlen(passed_path) - ft_strlen(ft_strchr(passed_path, '/'));
// 			ft_strlcpy(passed_path, passed_path + delete_len_for_passed_path_ptr + 1, ft_strlen(passed_path));
// 		}
// 		down_count_from_cwd--;
// 	}
// 	return passed_path;
// }

bool	get_pipe(t_pipex_data *pipex_data, int cmd_i)
{
	return (check_pipe(pipe(pipex_data->pipe_fd[cmd_i])));
}
