/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_absolute_path_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:14:49 by toshota           #+#    #+#             */
/*   Updated: 2023/12/02 23:17:30 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_cmd_absolute_path_count(t_pipex *pipex)
{
	int	count;

	count = 0;
	while (pipex->cmd_absolute_path[count])
		count++;
	return (count);
}

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

static void	add_slash_eos(char ***path)
{
	char	*tmp;
	int		i;

	i = 0;
	while (path[0][i])
	{
		tmp = path[0][i];
		path[0][i] = check_malloc(ft_strjoin(path[0][i], "/"));
		free(tmp);
		i++;
	}
}

static bool	add_absolute_from_env_path(char ***cmd_absolute_path, int cmd_i)
{
	char	**path;
	char	*tmp;
	int		i;

	if (check_getenv(getenv("PATH")) == false)
		return (false);
	path = check_malloc(ft_split(getenv("PATH"), ':'));
	add_slash_eos(&path);
	i = 0;
	while (path[i])
	{
		tmp = check_malloc(ft_strjoin(path[i], cmd_absolute_path[0][cmd_i]));
		if (is_file_exectable(tmp) == true)
		{
			free(cmd_absolute_path[0][cmd_i]);
			cmd_absolute_path[0][cmd_i] = check_malloc(ft_strdup(tmp));
			free(tmp);
			break ;
		}
		free(tmp);
		i++;
	}
	if (is_cmd_exist(path[i], cmd_absolute_path[0][cmd_i]) == false)
		return (all_free_tab(path), false);
	return (all_free_tab(path), true);
}

bool	add_absolute_path_to_cmd_name(char ***cmd_absolute_path)
{
	int	cmd_i;

	cmd_i = -1;
	while (cmd_absolute_path[0][++cmd_i])
	{
		if (is_cmd_builtin(cmd_absolute_path[0][cmd_i]) == true)
			continue ;
		if (is_cmd_relative_path(cmd_absolute_path, cmd_i))
			continue ;
		if (is_cmd_alreadly_absollute_path(cmd_absolute_path, cmd_i))
			continue ;
		if (add_absolute_from_env_path(cmd_absolute_path, cmd_i) == false)
			return (false);
	}
	return (true);
}
