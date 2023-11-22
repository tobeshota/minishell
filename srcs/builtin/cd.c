/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:39:21 by toshota           #+#    #+#             */
/*   Updated: 2023/11/22 15:17:25 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static bool	change_pwd(char *new_pwd, char ***envp)
{
	int		i;
	char	*tmp;

	i = 0;
	while (envp[0][i] && ft_strncmp(envp[0][i], "PWD=", ft_strlen("PWD=")))
		i++;
	if (is_path_found(envp[0][i]) == false)
		return (false);
	tmp = envp[0][i];
	envp[0][i] = check_malloc(ft_strjoin("PWD=", new_pwd));
	return (true);
}

static char *get_home(char ***envp)
{
	int env_i;

	env_i = 0;
	while (envp[0][env_i] && ft_strncmp(envp[0][env_i], "HOME=", ft_strlen("HOME=")))
		env_i++;
	if (is_path_found(envp[0][env_i]) == false)
		return (false);
	return envp[0][env_i] + ft_strlen("HOME=");
}

int	exec_cd(char **cmd, char ***envp)
{
	int		env_i;
	char	*path;
	char	**pwd;

	env_i = 0;
	while (envp[0][env_i] && ft_strncmp(envp[0][env_i], "PWD=", ft_strlen("PWD=")))
		env_i++;
	if (is_path_found(envp[0][env_i]) == false)
		return (false);
	if(cmd[1] == NULL)
		path = ft_strdup(get_home(envp));
	else
		path = ft_strdup(cmd[1]);
	pwd = ft_split(envp[0][env_i], ':');
	path_ptr = ft_split(path, ':');
	// envp[0][env_i] = get_pwd_for_relative_path(&pwd, get_down_count_from_pwd(path));
	convert_relative_path_to_absolute_path(&path_ptr, 0, *envp);

	all_free_tab(pwd);
	// free(path);

char **path_ptr;
path_ptr = ft_split(path, ':');
convert_relative_path_to_absolute_path(&path_ptr, 0, *envp);
	return (true);
	// char	**pwd;
	// char	*path;
	// char	*new_pwd;

	// if (get_pwd(&pwd, *envp) == false)
	// 	return (all_free_tab(pwd), false);

	// // get_cmd_parameter(cmd, &cmd, &path);
	// path = ft_strdup(cmd[1]);
	// new_pwd = get_pwd_for_relative_path(&pwd, get_down_count_from_pwd(path));
	// // pwdをpwd_for_relative_pathに変える
	// if (change_pwd(new_pwd, envp) == false)
	// 	return (all_free_tab(pwd), false);
	// all_free_tab(pwd);
	// free(path);
	// return (true);
}
