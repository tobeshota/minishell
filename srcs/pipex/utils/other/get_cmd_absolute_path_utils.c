/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_absolute_path_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:14:49 by toshota           #+#    #+#             */
/*   Updated: 2023/12/15 11:04:06 by toshota          ###   ########.fr       */
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

char	**add_slash_eos(char **path)
{
	char	*tmp;
	int		i;

	if (path == NULL)
		return (NULL);
	i = 0;
	while (path[i])
	{
		tmp = path[i];
		path[i] = check_malloc(ft_strjoin(path[i], "/"));
		free(tmp);
		tmp = NULL;
		i++;
	}
	return (path);
}

static bool	add_absolute_from_env_path(char **h_envp,
		char ***cmd_absolute_path, int cmd_i)
{
	char	**path;
	char	*tmp;
	char	*tmp_wo_encloser;
	int		i;

	if (check_getenv(getenv_from_h_envp(h_envp, "PATH")) == false)
		return (false);
	path = check_malloc \
	(add_slash_eos(ft_split(getenv_from_h_envp(h_envp, "PATH"), ':')));
	i = -1;
	while (path[++i])
	{
		tmp = check_malloc(ft_strjoin(path[i], cmd_absolute_path[0][cmd_i]));
		tmp_wo_encloser = omit_str(tmp, "\'\"");
		if (is_file_exectable(tmp_wo_encloser) == true)
		{
			free(cmd_absolute_path[0][cmd_i]);
			cmd_absolute_path[0][cmd_i] = check_malloc(ft_strdup(tmp));
			return (all_free_tab(path), free(tmp), free(tmp_wo_encloser), true);
		}
		free(tmp);
		free(tmp_wo_encloser);
	}
	return (all_free_tab(path), false);
}

bool	add_absolute_path_to_cmd_name(char **h_envp,
		char ***cmd_absolute_path)
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
		if (add_absolute_from_env_path(h_envp, cmd_absolute_path,
				cmd_i) == false)
			return (false);
	}
	return (true);
}
