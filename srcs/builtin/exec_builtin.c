/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:01:50 by toshota           #+#    #+#             */
/*   Updated: 2023/11/21 12:00:11 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static bool	is_specified_builtin_cmd(char *cmd, char *builtin_cmd)
{
	return (ft_strlen(cmd) == ft_strlen(builtin_cmd) && (!ft_strncmp(cmd,
				builtin_cmd, ft_strlen(cmd))));
}

bool	is_cmd_builtin(char *cmd)
{
	return (is_specified_builtin_cmd(cmd, "/bin/echo")
		|| is_specified_builtin_cmd(cmd, "/usr/bin/cd")
		|| is_specified_builtin_cmd(cmd, "/bin/pwd")
		|| is_specified_builtin_cmd(cmd, "export")
		|| is_specified_builtin_cmd(cmd, "unset")
		|| is_specified_builtin_cmd(cmd, "/usr/bin/env")
		|| is_specified_builtin_cmd(cmd, "exit"));
}

int	exec_builtin(char ***envp, t_pipex_data *pipex_data, int cmd_i)
{
	int		ret;
	char	**cmd;

	ret = false;
	cmd = check_malloc \
	(ft_split(pipex_data->cmd_absolute_path_with_parameter[cmd_i], ' '));
	if (is_specified_builtin_cmd(pipex_data->cmd_absolute_path[cmd_i], "/bin/echo"))
		ret = exec_echo(cmd, pipex_data);
	else if (is_specified_builtin_cmd(pipex_data->cmd_absolute_path[cmd_i], "/usr/bin/cd"))
		ret = exec_cd(cmd, envp) && exec_pwd(*envp, pipex_data);
	else if (is_specified_builtin_cmd(pipex_data->cmd_absolute_path[cmd_i], "/bin/pwd"))
		ret = exec_pwd(*envp, pipex_data);
	else if (is_specified_builtin_cmd(pipex_data->cmd_absolute_path[cmd_i], "export"))
		ret = exec_export(cmd, envp);
	else if (is_specified_builtin_cmd(pipex_data->cmd_absolute_path[cmd_i], "unset"))
		ret = exec_unset(envp);
	else if (is_specified_builtin_cmd(pipex_data->cmd_absolute_path[cmd_i], "/usr/bin/env"))
		ret = exec_env(*envp, pipex_data);
	else if (is_specified_builtin_cmd(pipex_data->cmd_absolute_path[cmd_i], "exit"))
		ret = exec_exit();
	all_free_tab(cmd);
	if(ret == false)
		return -1;
	return true;
}
