/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:39:21 by toshota           #+#    #+#             */
/*   Updated: 2023/11/29 17:39:29 by toshota          ###   ########.fr       */
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

static bool	update_envp(t_env **env, char *varname, char *new_data)
{
	char	*tmp;

	if (env == NULL)
		return (false);
	while ((*env)->next && ft_strncmp((*env)->content, varname, ft_strlen(varname)))
		ft_nodenext(env);
	if (is_path_found((*env)->content) == false)
		return (ft_nodefirst(env), false);
	new_data = check_malloc(ft_strjoin(varname, new_data));
	tmp = (*env)->content;
	(*env)->content = check_malloc(ft_strdup(new_data));
	ft_nodefirst(env);
	return (free(tmp), free(new_data), true);
}

static bool	update_old_pwd(t_env **env, t_pipex *pipex)
{
	char	**old_pwd;
	char	cwd[PATH_MAX];

	old_pwd = check_malloc(ft_split("export OLD_PWD", ' '));
	if (exec_export(old_pwd, env, pipex) == false)
		return (all_free_tab(old_pwd), false);
	if (getcwd(cwd, PATH_MAX) == NULL)
		return (all_free_tab(old_pwd), false);
	if (update_envp(env, "OLD_PWD=", cwd) == false)
		return (all_free_tab(old_pwd), false);
	return (all_free_tab(old_pwd), true);
}

int	exec_cd(char **cmd, t_env **env, t_pipex *pipex)
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
	update_old_pwd(env, pipex);
	if (chdir(path_from_cd) == -1)
		return (free(path_from_cd), false);
	free(path_from_cd);
	if (getcwd(cwd, PATH_MAX) == NULL)
		return (false);
	return (update_envp(env, "PWD=", cwd));
}
