/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:39:21 by toshota           #+#    #+#             */
/*   Updated: 2023/11/24 12:59:23 by toshota          ###   ########.fr       */
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

static bool	get_path_from_cmd_arg(char **path_ptr, char **cmd, char ***envp)
{
	char	*tmp;

	if (cmd[1] == NULL || is_match(cmd[1], "~") || is_match(cmd[1], "~/"))
		return (get_home(path_ptr, *envp));
	else if (cmd[1][0] == '~')
	{
		if (get_home(path_ptr, *envp) == false)
			return (false);
		tmp = *path_ptr;
		*path_ptr = check_malloc(ft_strjoin(*path_ptr, cmd[1]
					+ ft_strlen("~")));
		free(tmp);
	}
	else
		*path_ptr = check_malloc(ft_strdup(cmd[1]));
	return (true);
}

int	exec_cd(char **cmd, char ***envp)
{
	char	*path;

	if (get_path_from_cmd_arg(&path, cmd, envp) == false)
		return (free(path), false);
	if (is_match(path, ".") || is_match(path, "./"))
		return (free(path), true);
	if (is_file_exist(path) == false)
	{
		put_error("-bash: cd: ");
		put_error(path);
		put_error(": No such file or directory\n");
		return (free(path), true);
	}
	if (chdir(path) == -1)
		return (free(path), false);
	return (free(path), true);
}
