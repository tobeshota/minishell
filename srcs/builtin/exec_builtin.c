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

bool	is_match(char *cmd, char *builtin_cmd)
{
	return (ft_strlen(cmd) == ft_strlen(builtin_cmd) && (!ft_strncmp(cmd,
				builtin_cmd, ft_strlen(cmd))));
}

bool	is_cmd_builtin(char *cmd)
{
	return (is_match(cmd, "echo") || is_match(cmd, "/bin/echo")
		|| is_match(cmd, "cd") || is_match(cmd, "/usr/bin/cd")
		|| is_match(cmd, "pwd") || is_match(cmd, "/bin/pwd")
		|| is_match(cmd, "export") || is_match(cmd, "unset")
		|| is_match(cmd, "env") || is_match(cmd, "/usr/bin/env")
		|| is_match(cmd, "exit"));
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
	if (is_match(target, "/bin/echo") || is_match(target, "echo"))
		ret = exec_echo(cmd, pipex_data);
	else if (is_match(target, "/usr/bin/cd") || is_match(target, "cd"))
		ret = exec_cd(cmd, envp);
	else if (is_match(target, "/bin/pwd") || is_match(target, "pwd"))
		ret = exec_pwd(*envp, pipex_data);
	else if (is_match(target, "export"))
		ret = exec_export(cmd, envp);
	else if (is_match(target, "unset"))
		ret = exec_unset(envp);
	else if (is_match(target, "/usr/bin/env") || is_match(target, "env"))
		ret = exec_env(*envp, pipex_data);
	else if (is_match(target, "exit"))
		ret = exec_exit();
	return (all_free_tab(cmd), ret);
}
