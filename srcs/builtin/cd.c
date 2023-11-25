/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:39:21 by toshota           #+#    #+#             */
/*   Updated: 2023/11/25 21:02:20 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static bool	get_path_from_cd(char **path_ptr, char **cmd)
{
	char	*tmp;

	if (cmd[1] == NULL || is_match(cmd[1], "~") || is_match(cmd[1], "~/"))
	{
		*path_ptr = getenv("HOME");
		if (check_getenv(*path_ptr) == false)
			return (free(*path_ptr), false);
		*path_ptr = check_malloc(ft_strdup(*path_ptr));
		return (true);
	}
	else if (cmd[1][0] == '~')
	{
		*path_ptr = getenv("HOME");
		if (check_getenv(*path_ptr) == false)
			return (free(*path_ptr), false);
		*path_ptr = check_malloc(ft_strdup(*path_ptr));
		tmp = *path_ptr;
		*path_ptr = \
			check_malloc(ft_strjoin(*path_ptr, cmd[1] + ft_strlen("~")));
		free(tmp);
	}
	else
		*path_ptr = check_malloc(ft_strdup(cmd[1]));
	return (true);
}

static bool	update_envp(t_env **env_node, char *varname, char *new_data)
{
	char	*tmp;

	if (env_node == NULL)
		return (false);
	while (*env_node && ft_strncmp((*env_node)->content, varname,
			ft_strlen(varname)))
		ft_nodenext(env_node);
	if (is_path_found((*env_node)->content) == false)
		return (false);
	new_data = check_malloc(ft_strjoin(varname, new_data));
	tmp = (*env_node)->content;
	(*env_node)->content = check_malloc(ft_strdup(new_data));
	ft_nodefirst(env_node);
	return (free(tmp), free(new_data), true);
}

int	exec_cd(char **cmd, t_env **env_node)
{
	char	*path_from_cd;
	char	cwd[PATH_MAX];

	if (get_path_from_cd(&path_from_cd, cmd) == false)
		return (free(path_from_cd), false);
	if (is_match(path_from_cd, ".") || is_match(path_from_cd, "./"))
		return (free(path_from_cd), true);
	if (is_file_exist(path_from_cd) == false)
	{
		put_error("-bash: cd: ");
		put_error(path_from_cd);
		put_error(": No such file or directory\n");
		return (free(path_from_cd), true);
	}
	if (chdir(path_from_cd) == -1)
		return (free(path_from_cd), false);
	free(path_from_cd);
	if (getcwd(cwd, PATH_MAX) == NULL)
		return (false);
	return (update_envp(env_node, "PWD=", cwd));
}
