/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_arg_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 21:49:47 by toshota           #+#    #+#             */
/*   Updated: 2023/12/19 23:36:24 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static bool	is_cmd_param_included_except_dot_slash(char *cmd_parameter)
{
	int	i;

	i = 0;
	while (cmd_parameter[i])
	{
		if (cmd_parameter[i] != '.' && cmd_parameter[i] != '/')
			return (true);
		i++;
	}
	return (false);
}

bool	is_parameter_dir(char *cmd_parameter)
{
	DIR	*dir;

	dir = opendir(cmd_parameter);
	if (dir == NULL)
		return (false);
	return (closedir(dir), true);
}

static bool	is_parameter_file(char *cmd_parameter)
{
	int			target_fd;
	char		*cmd_param_wo_encloser;
	struct stat	st;

	cmd_param_wo_encloser = omit_str(cmd_parameter, "\'\"");
	target_fd = open_file(cmd_param_wo_encloser, INFILE);
	if (target_fd == -1)
		return (free(cmd_param_wo_encloser), false);
	else if (check_close(close(target_fd)) == false)
		return (free(cmd_param_wo_encloser), false);
	else if (stat(cmd_param_wo_encloser, &st) < 0)
		return (ft_putendl_fd("failt to stat", STDERR_FILENO), false);
	else if (S_ISDIR(st.st_mode))
		return (free(cmd_param_wo_encloser), false);
	else if (cmd_param_wo_encloser[0] == '-')
		return (free(cmd_param_wo_encloser), false);
	else if (is_file_exist(cmd_param_wo_encloser) == false)
		return (free(cmd_param_wo_encloser), false);
	else if (!is_cmd_param_included_except_dot_slash(cmd_param_wo_encloser))
		return (free(cmd_param_wo_encloser), false);
	return (free(cmd_param_wo_encloser), true);
}

int	get_cmd_arg_fd(t_pipex *pipex, int cmd_i)
{
	int		cmd_arg_fd;
	char	*cmd_parameter;

	cmd_parameter = check_malloc \
	(ft_substr(pipex->cmd_absolute_path_with_parameter[cmd_i], \
	strlen_until_c \
	(pipex->cmd_absolute_path_with_parameter[cmd_i], ' ') + 1, \
	ft_strlen(pipex->cmd_absolute_path_with_parameter[cmd_i])));
	if (is_parameter_file(cmd_parameter) == true)
		cmd_arg_fd = open_file(cmd_parameter, INFILE);
	else
		cmd_arg_fd = NOT_SPECIFIED;
	free(cmd_parameter);
	return (cmd_arg_fd);
}
