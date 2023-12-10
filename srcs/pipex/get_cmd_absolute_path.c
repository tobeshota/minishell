/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_absolute_path.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:14:49 by toshota           #+#    #+#             */
/*   Updated: 2023/12/10 22:27:11 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	get_cmd_name_from_arg(char **argv, char **h_envp,
		char ***cmd_absolute_path)
{
	int	arg_i;
	int	cmd_i;

	*cmd_absolute_path = (char **)check_malloc \
	(malloc(sizeof(char *) * (get_cmd_count(argv, h_envp) + 1)));
	arg_i = 0;
	cmd_i = 0;
	while (argv[arg_i])
	{
		if (is_cmd(argv, arg_i, h_envp) == true)
		{
			cmd_absolute_path[0][cmd_i] = check_malloc \
			(ft_substr(argv[arg_i], 0, strlen_until_c(argv[arg_i], ' ')));
			cmd_i++;
		}
		arg_i++;
	}
	cmd_absolute_path[0][cmd_i] = NULL;
}

static char	**get_cmd_parameter(char **argv, char **h_envp,
		char ***cmd_absolute_path, t_pipex *pipex)
{
	int		arg_i;
	int		cmd_i;
	char	**cmd_parameter;

	arg_i = 0;
	cmd_i = 0;
	cmd_parameter = (char **)check_malloc \
	(malloc(sizeof(char *) * (get_cmd_absolute_path_count(pipex) + 1)));
	while (argv[arg_i])
	{
		if (is_cmd(argv, arg_i, h_envp) == true)
		{
			cmd_parameter[cmd_i] = check_malloc(ft_substr(argv[arg_i], \
			ft_strlen(cmd_absolute_path[0][cmd_i]), ft_strlen(argv[arg_i])));
			cmd_i++;
		}
		arg_i++;
	}
	cmd_parameter[cmd_i] = NULL;
	return (cmd_parameter);
}

static void	get_cmd_absolute_path_with_parameter(char ***cmd_parameter, \
t_pipex *pipex)
{
	int	cmd_i;

	cmd_i = 0;
	pipex->cmd_absolute_path_with_parameter = (char **)check_malloc \
		(malloc(sizeof(char *) * (get_cmd_absolute_path_count(pipex) + 1)));
	while (pipex->cmd_absolute_path[cmd_i])
	{
		pipex->cmd_absolute_path_with_parameter[cmd_i] = check_malloc \
		(ft_strjoin(pipex->cmd_absolute_path[cmd_i], cmd_parameter[0][cmd_i]));
		cmd_i++;
	}
	pipex->cmd_absolute_path_with_parameter[cmd_i] = NULL;
}

bool	get_cmd_absolute_path(char **h_envp, t_pipex *pipex)
{
	char	**cmd_parameter;

	get_cmd_name_from_arg(pipex->argv, h_envp, &pipex->cmd_absolute_path);
	cmd_parameter = get_cmd_parameter \
	(pipex->argv, h_envp, &pipex->cmd_absolute_path, pipex);
	if (add_absolute_path_to_cmd_name \
	(h_envp, &pipex->cmd_absolute_path) == false)
		return (all_free_tab(cmd_parameter), false);
	get_cmd_absolute_path_with_parameter(&cmd_parameter, pipex);
	return (all_free_tab(cmd_parameter), true);
}
