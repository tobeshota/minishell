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

static bool	is_builitin(char *cmd, char *builtin_cmd)
{
	return (ft_strlen(cmd) == ft_strlen(builtin_cmd) && (!ft_strncmp(cmd,
				builtin_cmd, ft_strlen(cmd))));
}

bool	is_cmd_builtin(char *cmd)
{
	return (is_builitin(cmd, "echo") || is_builitin(cmd, "/bin/echo")
		|| is_builitin(cmd, "cd") || is_builitin(cmd, "/usr/bin/cd")
		|| is_builitin(cmd, "pwd") || is_builitin(cmd, "/bin/pwd")
		|| is_builitin(cmd, "export") || is_builitin(cmd, "unset")
		|| is_builitin(cmd, "env") || is_builitin(cmd, "/usr/bin/env")
		|| is_builitin(cmd, "exit"));
}

int	exec_builtin(char ***envp, t_pipex_data *pipex_data, int cmd_i)
{
	int		ret;
	char	**cmd;
	char	*target;

	ret = false;
	target = pipex_data->cmd_absolute_path[cmd_i];
	cmd = check_malloc \
	(ft_split(pipex_data->cmd_absolute_path_with_parameter[cmd_i], ' '));
	if (is_builitin(target, "/bin/echo") || is_builitin(target, "echo"))
		ret = exec_echo(cmd, pipex_data);
	else if (is_builitin(target, "/usr/bin/cd") || is_builitin(target, "cd"))
		ret = exec_cd(cmd, envp);
	else if (is_builitin(target, "/bin/pwd") || is_builitin(target, "pwd"))
		ret = exec_pwd(*envp, pipex_data);
	else if (is_builitin(target, "export"))
		ret = exec_export(cmd, envp);
	else if (is_builitin(target, "unset"))
		ret = exec_unset(envp);
	else if (is_builitin(target, "/usr/bin/env") || is_builitin(target, "env"))
		ret = exec_env(*envp, pipex_data);
	else if (is_builitin(target, "exit"))
		ret = exec_exit();
	return (all_free_tab(cmd), ret);
}
