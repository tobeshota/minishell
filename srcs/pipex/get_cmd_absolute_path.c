/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_absolute_path.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:14:49 by toshota           #+#    #+#             */
/*   Updated: 2023/12/16 22:28:43 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// get_cmd_name_from_arg(pipex->argv, h_envp, &pipex->cmd_absolute_path)
static bool	get_cmd_name_from_arg(char **h_envp, t_pipex *pipex)
{
	int		cmd_count;
	int		arg_i;
	int		cmd_i;
	char	**cmd_array;

	cmd_count = get_cmd_count(pipex, h_envp);
	if (cmd_count == false)
		return (false);
	pipex->cmd_absolute_path = (char **)check_malloc \
	(malloc(sizeof(char *) * (cmd_count + 1)));
	arg_i = 0;
	cmd_i = 0;
	while (pipex->argv[arg_i])
	{
		cmd_array = split_wo_enclosed_str(pipex->argv[arg_i], ' ');
		if (is_cmd(cmd_array, 0, h_envp) == true)
		{
			pipex->cmd_absolute_path[cmd_i] = check_malloc \
			(ft_substr(pipex->argv[arg_i], 0, strlen_until_c(pipex->argv[arg_i], ' ')));
			cmd_i++;
		}
		all_free_tab(cmd_array);
		arg_i++;
	}
	pipex->cmd_absolute_path[cmd_i] = NULL;
	return (true);
}

static char	**get_cmd_parameter(char **h_envp, t_pipex *pipex)
{
	int		arg_i;
	int		cmd_i;
	char	**cmd_parameter;
	char	**cmd_array;

	arg_i = 0;
	cmd_i = 0;
	cmd_parameter = (char **)check_malloc \
	(malloc(sizeof(char *) * (get_cmd_absolute_path_count(pipex) + 1)));
	while (pipex->argv[arg_i])
	{
		cmd_array = split_wo_enclosed_str(pipex->argv[arg_i], ' ');
		if (is_cmd(cmd_array, 0, h_envp) == true)
		{
			cmd_parameter[cmd_i] = check_malloc(ft_substr(pipex->argv[arg_i], \
			ft_strlen(pipex->cmd_absolute_path[cmd_i]), ft_strlen(pipex->argv[arg_i])));
			cmd_i++;
		}
		all_free_tab(cmd_array);
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

	if (get_cmd_name_from_arg(h_envp, pipex) == false)
		return (false);
	cmd_parameter = get_cmd_parameter(h_envp, pipex);
	if (add_absolute_path_to_cmd_name \
	(h_envp, &pipex->cmd_absolute_path) == false)
		return (all_free_tab(cmd_parameter), false);
	get_cmd_absolute_path_with_parameter(&cmd_parameter, pipex);
	return (all_free_tab(cmd_parameter), true);
}
