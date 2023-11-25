/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_absolute_path.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:14:49 by toshota           #+#    #+#             */
/*   Updated: 2023/11/25 19:28:31 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	get_cmd_name_from_arg(char **argv, char ***cmd_absolute_path)
{
	int	arg_i;
	int	cmd_i;

	*cmd_absolute_path = (char **)check_malloc(malloc(sizeof(char *)
				* (get_cmd_count(argv) + 1)));
	arg_i = 0;
	cmd_i = 0;
	while (argv[arg_i])
	{
		if (is_cmd(argv, arg_i))
		{
			cmd_absolute_path[0][cmd_i] = check_malloc(ft_substr(argv[arg_i], 0,
						strlen_until_c(argv[arg_i], ' ')));
			cmd_i++;
		}
		arg_i++;
	}
	cmd_absolute_path[0][cmd_i] = NULL;
}

void	get_cmd_parameter(char **argv, char ***cmd_absolute_path,
		char ***cmd_parameter)
{
	int	arg_i;
	int	cmd_i;

	*cmd_parameter = (char **)check_malloc(malloc(sizeof(char *)
				* (get_cmd_count(argv) + 1)));
	arg_i = 0;
	cmd_i = 0;
	while (argv[arg_i])
	{
		if (is_cmd(argv, arg_i))
		{
			cmd_parameter[0][cmd_i] = check_malloc(ft_substr(argv[arg_i],
						ft_strlen(cmd_absolute_path[0][cmd_i]),
						ft_strlen(argv[arg_i])));
			cmd_i++;
		}
		arg_i++;
	}
	cmd_parameter[0][cmd_i] = NULL;
}

static void	get_cmd_absolute_path_with_parameter(char **argv,
		char ***cmd_parameter, t_pipex_data *pipex_data)
{
	int	cmd_i;

	pipex_data->cmd_absolute_path_with_parameter = \
	(char **)check_malloc(malloc(sizeof(char *) * (get_cmd_count(argv) + 1)));
	cmd_i = 0;
	while (pipex_data->cmd_absolute_path[cmd_i])
	{
		pipex_data->cmd_absolute_path_with_parameter[cmd_i] = \
		check_malloc(ft_strjoin(pipex_data->cmd_absolute_path[cmd_i], \
		cmd_parameter[0][cmd_i]));
		cmd_i++;
	}
	pipex_data->cmd_absolute_path_with_parameter[cmd_i] = NULL;
}

bool	get_cmd_absolute_path(char **argv, t_pipex_data *pipex_data)
{
	char	**cmd_parameter;

	get_cmd_name_from_arg(argv, &pipex_data->cmd_absolute_path);
	get_cmd_parameter(argv, &pipex_data->cmd_absolute_path, &cmd_parameter);
	if (add_absolute_path_to_cmd_name(&pipex_data->cmd_absolute_path) == false)
		return (all_free_tab(cmd_parameter), false);
	get_cmd_absolute_path_with_parameter(argv, &cmd_parameter, pipex_data);
	all_free_tab(cmd_parameter);
	return (true);
}
