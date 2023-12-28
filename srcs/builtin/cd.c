/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:39:21 by toshota           #+#    #+#             */
/*   Updated: 2023/12/28 15:30:03 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static bool	update_oldpwd(t_env **env, t_pipex *pipex)
{
	char	**oldpwd;
	char	cwd[PATH_MAX];

	oldpwd = check_malloc(ft_split("export OLDPWD", ' '));
	if (exec_export(oldpwd, env, pipex) == false)
		return (all_free_tab(oldpwd), false);
	if (getcwd(cwd, PATH_MAX) == NULL)
		return (all_free_tab(oldpwd), false);
	if (update_envp(env, "OLDPWD=", cwd) == false)
		return (all_free_tab(oldpwd), false);
	return (all_free_tab(oldpwd), true);
}

static int	change_oldpwd(char **path_ptr, t_env **env, t_pipex *pipex)
{
	while ((*env)->next && ft_strncmp((*env)->content, "OLDPWD=",
			ft_strlen("OLDPWD=")))
		ft_nodenext(env);
	if (ft_strncmp((*env)->content, "OLDPWD=", ft_strlen("OLDPWD=")))
	{
		*pipex->error_num = 1;
		put_error("-minishell: cd: OLDPWD not set\n");
		ft_nodefirst(env);
		return (false);
	}
	*path_ptr = check_malloc(ft_strdup((*env)->content + ft_strlen("OLDPWD=")));
	ft_putendl_fd(*path_ptr, pipex->outfile_fd);
	ft_nodefirst(env);
	if (update_oldpwd(env, pipex) == false)
		return (free(*path_ptr), false);
	return (true);
}

static bool	get_path_from_cd(char **path_ptr, char **cmd, t_env **env,
		t_pipex *pipex)
{
	char	*tmp;

	if (cmd[1] == NULL || cmd[1][0] == '~')
	{
		*path_ptr = getenv("HOME");
		if (check_getenv(*path_ptr) == false)
			return (false);
		*path_ptr = check_malloc(ft_strdup(*path_ptr));
		if (cmd[1] && is_match(cmd[1], "~") == false && is_match(cmd[1],
				"~/") == false)
		{
			tmp = *path_ptr;
			*path_ptr = check_malloc \
			(ft_strjoin(*path_ptr, cmd[1] + ft_strlen("~")));
			free(tmp);
		}
	}
	else if (cmd[1] && is_match(cmd[1], "-"))
	{
		if (change_oldpwd(path_ptr, env, pipex) == false)
			return (false);
	}
	else
		*path_ptr = check_malloc(ft_strdup(cmd[1]));
	return (true);
}

static void	put_parent_dir_error(void)
{
	put_error("cd: error retrieving current directory: ");
	put_error("getcwd: cannot access parent directories: ");
	put_error("No such file or directory\n");
}

int	exec_cd(char **cmd, t_env **env, t_pipex *pipex)
{
	char	*path_from_cd;
	char	cwd[PATH_MAX];

	if (get_path_from_cd(&path_from_cd, cmd, env, pipex) == false)
		return (false);
	if (get_element_count(cmd) > 2)
		return (free(path_from_cd), \
		put_error_w_cmd_filename("cd", 0, "too many arguments", pipex), false);
	if (is_match(path_from_cd, ".") || is_match(path_from_cd, "./") || \
	is_match(path_from_cd, """") || is_match(path_from_cd, "''"))
	{
		if (getcwd(cwd, PATH_MAX) == NULL)
			put_parent_dir_error();
		return (free(path_from_cd), true);
	}
	if (is_parameter_dir(path_from_cd) == false)
		return (put_file_error("cd", path_from_cd, pipex), \
		free(path_from_cd), false);
	update_oldpwd(env, pipex);
	if (chdir(path_from_cd) == -1)
		return (free(path_from_cd), false);
	free(path_from_cd);
	if (getcwd(cwd, PATH_MAX) == NULL)
		return (put_parent_dir_error(), false);
	return (update_envp(env, "PWD=", cwd));
}
