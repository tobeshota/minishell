/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_arg_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 21:49:47 by toshota           #+#    #+#             */
/*   Updated: 2023/12/05 20:45:39 by toshota          ###   ########.fr       */
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
	DIR *dir;

	dir = opendir(cmd_parameter);
	if (dir == NULL)
		return false;
	return closedir(dir), true;
}

bool	is_parameter_file(char *cmd_parameter)
{
	int			fd_for_checking_non_directory;
	struct stat	st;

	fd_for_checking_non_directory = open_file(cmd_parameter, INFILE);
	if (fd_for_checking_non_directory == -1)
		return (false);
	else if (check_close(close(fd_for_checking_non_directory)) == false)
		return (false);
	else if (stat(cmd_parameter, &st) < 0)
		return (ft_putstr_fd("failt to stat", STDERR_FILENO), false);
	else if (S_ISDIR(st.st_mode))
		return (false);
	else if (cmd_parameter[0] == '-')
		return (false);
	else if (is_file_exist(cmd_parameter) == false)
		return (false);
	else if (is_cmd_param_included_except_dot_slash(cmd_parameter) == false)
		return (false);
	return (true);
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
