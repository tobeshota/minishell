/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_absolute_path_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:14:49 by toshota           #+#    #+#             */
/*   Updated: 2023/11/23 22:51:34 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static bool	is_cmd_exist(char *env_path, char *cmd)
{
	if (is_cmd_builtin(cmd))
		return (true);
	if (env_path == NULL)
	{
		put_error("-bash: ");
		put_error(cmd);
		put_error(": command not found\n");
		return (false);
	}
	return (true);
}

static bool	add_absolute_from_env_path(char ***cmd_absolute_path,
		char **env_path, int cmd_i)
{
	int		env_i;
	char	*tmp;
	char	*cmd;

	cmd = check_malloc(ft_strdup(cmd_absolute_path[0][cmd_i]));
	env_i = 0;
	while (env_path[env_i])
	{
		tmp = check_malloc(ft_strjoin(env_path[env_i],
					cmd_absolute_path[0][cmd_i]));
		if (is_file_exectable(tmp) == true)
		{
			free(cmd_absolute_path[0][cmd_i]);
			cmd_absolute_path[0][cmd_i] = check_malloc(ft_strdup(tmp));
			free(tmp);
			break ;
		}
		free(tmp);
		env_i++;
	}
	if (is_cmd_exist(env_path[env_i], cmd) == false)
		return (free(cmd), false);
	return (free(cmd), true);
}

void	delete_relative_path(char ***cmd_absolute_path, int cmd_i)
{
	char	*tmp;

	tmp = cmd_absolute_path[0][cmd_i];
	cmd_absolute_path[0][cmd_i] = check_malloc(ft_strtrim(cmd_absolute_path[0][cmd_i], "../"));
	free(tmp);
	tmp = cmd_absolute_path[0][cmd_i];
	cmd_absolute_path[0][cmd_i] = check_malloc(ft_strtrim(cmd_absolute_path[0][cmd_i], "./"));
	free(tmp);
}

// bool	convert_relative_path_to_absolute_path(char ***path,
// 		int cmd_i, char **envp)
// {
// 	char	*tmp;
// 	char	**pwd;
// 	char	*pwd_for_relative_path;

// 	if (get_pwd(&pwd, envp) == false)
// 		return (false);
// 	pwd_for_relative_path = down_cwd(pwd, get_down_count_from_cwd(path[0][cmd_i]));
// 	delete_relative_path(path, cmd_i);

// 	if(ft_strlen(path[0][cmd_i]))
// 	{
// 		tmp = path[0][cmd_i];
// 		path[0][cmd_i] = check_malloc(ft_strjoin("/", path[0][cmd_i]));
// 		free(tmp);
// 	}
// 	tmp = path[0][cmd_i];
// 	path[0][cmd_i] = check_malloc(ft_strjoin(pwd_for_relative_path, path[0][cmd_i]));
// 	free(tmp);

// 	all_free_tab(pwd);
// 	// free(pwd_for_relative_path);
// 	return (true);
// }

bool	add_absolute_path_to_cmd_name(char ***cmd_absolute_path,
		char **env_path, char **envp)
{
	int	cmd_i;

	cmd_i = -1;
	while (cmd_absolute_path[0][++cmd_i])
	{
		if (is_cmd_relative_path(cmd_absolute_path, cmd_i))
			continue ;
		if (is_cmd_alreadly_absollute_path(cmd_absolute_path, cmd_i))
			continue ;
		if (add_absolute_from_env_path(cmd_absolute_path, env_path,
				cmd_i) == false)
			return (false);
	}
	return (true);
}
