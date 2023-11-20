/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:01:50 by toshota           #+#    #+#             */
/*   Updated: 2023/11/20 14:30:57 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildin.h"

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

int	execve_builtin(char *cmd, char **cmd_with_parameter, char ***envp,
		t_pipex_data *pipex_data)
{
	if (is_specified_builtin_cmd(cmd, "/bin/echo"))
		return (execve_echo(cmd_with_parameter, pipex_data));
	else if (is_specified_builtin_cmd(cmd, "/usr/bin/cd"))
		return (execve_cd(cmd_with_parameter, envp));
	else if (is_specified_builtin_cmd(cmd, "/bin/pwd"))
		return (execve_pwd(*envp, pipex_data));
	else if (is_specified_builtin_cmd(cmd, "export"))
		return (execve_export(cmd_with_parameter, envp));
	else if (is_specified_builtin_cmd(cmd, "unset"))
		return (execve_unset(envp));
	else if (is_specified_builtin_cmd(cmd, "/usr/bin/env"))
		return (execve_env(*envp, pipex_data));
	else if (is_specified_builtin_cmd(cmd, "exit"))
		return (execve_exit());
	else
		return (false);
}
