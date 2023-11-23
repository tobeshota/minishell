/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:39:21 by toshota           #+#    #+#             */
/*   Updated: 2023/11/23 21:54:51 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static bool	get_home(char **path_ptr, char **envp)
{
	int	env_i;

	env_i = 0;
	while (envp[env_i] && ft_strncmp(envp[env_i], "HOME=", ft_strlen("HOME=")))
		env_i++;
	if (is_path_found(envp[env_i]) == false)
		return (false);
	*path_ptr = check_malloc(ft_strdup(envp[env_i] + ft_strlen("HOME=")));
	return (true);
}

static bool	is_path_alreadly_absollute_path(char *path)
{
	return (path[0] == '/' && (path[1] == '\0' || ft_strchr(&path[1], '/')));
}

static bool	get_path_from_cmd_arg(char **path_ptr, char **cmd, char ***envp)
{
	if (cmd[1] == NULL)
		return (get_home(path_ptr, *envp));
	else
		*path_ptr = check_malloc(ft_strdup(cmd[1]));
	return (true);
}

// cd ..が/Users/tobeshota以降行かない！
bool	change_current_directory(char ***envp, int env_i, char *path)
{
	int		down_count_from_cwd;
	char	*tmp;

	if (is_path_alreadly_absollute_path(path))
	{
		tmp = path;
		path = check_malloc(ft_strjoin("PWD=", path));
		ft_strlcpy(envp[0][env_i], path, ft_strlen(path) + 1);
	}
	else
	{
		if (is_file_exist(path) == false)
			return (put_error("-bash: cd: "), put_error(path),
				put_error(": No such file or directory\n"), free(path), true);
		down_count_from_cwd = get_down_count_from_cwd(path);
		envp[0][env_i] = down_path(envp[0][env_i], down_count_from_cwd);
		path = down_path(path, down_count_from_cwd);
		tmp = path;
		path = check_malloc(ft_strjoin(envp[0][env_i], path));
		ft_strlcpy(envp[0][env_i], path, ft_strlen(path) + 1);
		if (!ft_strncmp(envp[0][env_i], "PWD=", ft_strlen(envp[0][env_i])))
			ft_strlcpy(envp[0][env_i], "PWD=/", ft_strlen("PWD=/") + 1);
	}
	return (free(path), free(tmp), true);
}

int	exec_cd(char **cmd, char ***envp)
{
	int		env_i;
	char	*path;

	env_i = 0;
	while (envp[0][env_i] && ft_strncmp(envp[0][env_i], "PWD=",
			ft_strlen("PWD=")))
		env_i++;
	if (is_path_found(envp[0][env_i]) == false)
		return (false);
	if (get_path_from_cmd_arg(&path, cmd, envp) == false)
		return (free(path), false);
	if (!ft_strncmp(path, ".", ft_strlen(path)))
		return (free(path), true);
	return (change_current_directory(envp, env_i, path));
}
