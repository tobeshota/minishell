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

bool	is_under_bar(char *cmd)
{
	return (is_match(cmd, "_") || (ft_strlen(cmd) >= 2 && !ft_strncmp(cmd, "_=",
				2)));
}

bool	is_match(char *s1, char *s2)
{
	return (s1 && s2 && ft_strlen(s1) == ft_strlen(s2) && (!ft_strncmp(s1, s2,
				ft_strlen(s1))));
}

bool	is_cmd_builtin(char *cmd)
{
	return (is_match(cmd, "echo") || is_match(cmd, "/bin/echo") || is_match(cmd,
			"cd") || is_match(cmd, "/usr/bin/cd") || is_match(cmd, "pwd")
		|| is_match(cmd, "/bin/pwd") || is_match(cmd, "export") || is_match(cmd,
			"unset") || is_match(cmd, "env") || is_match(cmd, "/usr/bin/env")
		|| is_match(cmd, "exit"));
}

bool	update_envp(t_env **env, char *varname, char *new_data)
{
	char	*tmp;

	if (env == NULL)
		return (false);
	while ((*env)->next && ft_strncmp((*env)->content, varname,
			ft_strlen(varname)))
		ft_nodenext(env);
	if (is_path_found((*env)->content) == false)
		return (ft_nodefirst(env), false);
	new_data = check_malloc(ft_strjoin(varname, new_data));
	tmp = (*env)->content;
	(*env)->content = check_malloc(ft_strdup(new_data));
	ft_nodefirst(env);
	return (free(tmp), free(new_data), true);
}

int	exec_builtin(t_env **env, t_pipex *pipex, int cmd_i)
{
	int		ret;
	char	**cmd;
	char	*target;

	ret = false;
	target = pipex->cmd_absolute_path[cmd_i];
	cmd = check_malloc(split_wo_enclosed_str \
	(pipex->cmd_absolute_path_with_parameter[cmd_i], ' '));
	if (is_match(target, "/bin/echo") || is_match(target, "echo"))
		ret = exec_echo(cmd, pipex);
	else if (is_match(target, "/usr/bin/cd") || is_match(target, "cd"))
		ret = exec_cd(cmd, env, pipex);
	else if (is_match(target, "/bin/pwd") || is_match(target, "pwd"))
		ret = exec_pwd(pipex);
	else if (is_match(target, "export"))
		ret = exec_export(cmd, env, pipex);
	else if (is_match(target, "unset"))
		ret = exec_unset(cmd, env);
	else if (is_match(target, "/usr/bin/env") || is_match(target, "env"))
		ret = exec_env(env, pipex);
	else if (is_match(target, "exit"))
		ret = exec_exit(cmd, pipex);
	return (all_free_tab(cmd), ret);
}
