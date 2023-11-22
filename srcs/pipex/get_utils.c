/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:14:49 by toshota           #+#    #+#             */
/*   Updated: 2023/11/22 14:43:25 by toshota          ###   ########.fr       */
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
	while (*envp && ft_strncmp(*envp, "PWD=", ft_strlen("PWD=")))
		(*envp)++;
	if (is_path_found(*envp) == false)
		return (false);
	*pwd_path = check_malloc(ft_split(*envp + ft_strlen("PWD="), ':'));
	add_slash_eos(pwd_path);
	return (true);
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
	// 最後だけ..が考えられる cd ..
	// if (ft_strnstr(relative_path, "..", ft_strlen("..")))
	// {
	// 	down_count_from_pwd++;
	// 	relative_path += ft_strlen("..");
	// }
	return (down_count_from_pwd);
}

static int is_eof_c(char *str, char c)
{
	return str[ft_strlen(str)-1] == c;
}

// 引数として渡ってくる**pwd_path: "/Users/tobeshota/workspace/42/minishell/"
char	*get_pwd_for_relative_path(char ***pwd_path, int down_count_from_pwd)
{
	// down_count_from_pwdの数ぶんだけ/を下げる．
	int		delete_len;
	char	*tmp;

	// 最初が/ならdown_count_from_pwdを1つ加算する．
	if(is_eof_c(pwd_path[0][0], '/'))
	// if(pwd_path[0][0][ft_strlen(pwd_path[0][0]) - 1] == '/')
		down_count_from_pwd++;

	while(down_count_from_pwd)
	{
		delete_len = ft_strlen(pwd_path[0][0]) - ft_strlen(ft_strrchr(pwd_path[0][0], '/'));

		tmp = pwd_path[0][0];
		pwd_path[0][0] = ft_substr(pwd_path[0][0], 0, delete_len);
		free(tmp);
		tmp = NULL;
		down_count_from_pwd--;
	}
	return pwd_path[0][0];




	// int		delete_len;
	// char	*pwd_for_relative_path;

	// if (ft_strrnchr(pwd_path[0][0], '/', down_count_from_pwd) == NULL)
	// 	delete_len = 0;
	// else
	// 	delete_len = ft_strlen(ft_strrnchr(pwd_path[0][0], '/',
	// 				down_count_from_pwd) + 1);
	// pwd_for_relative_path = check_malloc(ft_substr(pwd_path[0][0], 0,
	// 			ft_strlen(pwd_path[0][0]) - delete_len));
	// return (pwd_for_relative_path);
}

bool	get_pipe(t_pipex_data *pipex_data, int cmd_i)
{
	return (check_pipe(pipe(pipex_data->pipe_fd[cmd_i])));
}
