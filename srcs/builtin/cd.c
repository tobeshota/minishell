/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:39:21 by toshota           #+#    #+#             */
/*   Updated: 2023/11/21 12:09:51 by toshota          ###   ########.fr       */
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

int	exec_cd(char **cmd_with_parameter, char ***envp)
{
	char	**pwd;
	char	**cmd_parameter;
	char	*new_pwd;

	if (get_pwd(&pwd, *envp) == false)
		return (all_free_tab(pwd), false);

	get_cmd_parameter(cmd_with_parameter, &cmd_with_parameter, &cmd_parameter);
	new_pwd = get_pwd_for_relative_path(&pwd, get_down_count_from_pwd(*cmd_parameter));
	// pwdをpwd_for_relative_pathに変える
	if (change_pwd(new_pwd, envp) == false)
		return (all_free_tab(pwd), all_free_tab(cmd_parameter), false);
	all_free_tab(pwd);
	all_free_tab(cmd_parameter);
	return (true);
}
