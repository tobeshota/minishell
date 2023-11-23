/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_β.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 11:14:04 by toshota           #+#    #+#             */
/*   Updated: 2023/11/23 15:53:47 by toshota          ###   ########.fr       */
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

int	exec_cd(char **cmd, char ***envp)
{
	char	**pwd;
	char	**cmd_parameter;
	char	*pwd_for_relative_path;

	if (get_pwd(&pwd, *envp) == false)
		return (all_free_tab(pwd), false);

	get_cmd_parameter(cmd, &cmd, &cmd_parameter);
	pwd_for_relative_path = down_path(&pwd, get_down_count_from_cwd(*cmd_parameter));
	// pwdをpwd_for_relative_pathに変える
	if (change_pwd(pwd_for_relative_path, envp) == false)
		return (all_free_tab(pwd), all_free_tab(cmd_parameter), false);
	all_free_tab(pwd);
	all_free_tab(cmd_parameter);
	return (true);
}
