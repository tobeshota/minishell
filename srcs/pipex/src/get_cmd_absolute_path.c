/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_absolute_path.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:14:49 by toshota           #+#    #+#             */
/*   Updated: 2023/11/17 12:35:03 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static void	get_cmd_name_from_arg(char **argv, char ***cmd_absolute_path)
{
	int	arg_i;
	int	cmd_i;

	*cmd_absolute_path = (char **)malloc(sizeof(char *) * (get_cmd_count(argv) + 1));
	check_malloc(*cmd_absolute_path);
	arg_i = 0;
	cmd_i = 0;
	while (argv[arg_i])
	{
		if (is_cmd(argv, arg_i))
		{
			cmd_absolute_path[0][cmd_i] = ft_substr(argv[arg_i], 0,
					strlen_until_c(argv[arg_i], ' '));
			check_malloc(cmd_absolute_path[0][cmd_i]);
			cmd_i++;
		}
		arg_i++;
	}
	cmd_absolute_path[0][cmd_i] = NULL;
}

static void	get_cmd_parameter(char **argv, char ***cmd_absolute_path,
		char ***cmd_parameter)
{
	int	arg_i;
	int	cmd_i;

	*cmd_parameter = (char **)malloc(sizeof(char *) * (get_cmd_count(argv)
				+ 1));
	check_malloc(*cmd_parameter);
	arg_i = 0;
	cmd_i = 0;
	while (argv[arg_i])
	{
		if (is_cmd(argv, arg_i))
		{
			cmd_parameter[0][cmd_i] = ft_substr(argv[arg_i],
					ft_strlen(cmd_absolute_path[0][cmd_i]),
					ft_strlen(argv[arg_i]));
			check_malloc(cmd_parameter[0][cmd_i]);
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

	pipex_data->cmd_absolute_path_with_parameter = (char **)malloc(sizeof(char *)
			* (get_cmd_count(argv) + 1));
	check_malloc(pipex_data->cmd_absolute_path_with_parameter);
	cmd_i = 0;
	while (pipex_data->cmd_absolute_path[cmd_i])
	{
		pipex_data->cmd_absolute_path_with_parameter[cmd_i] \
		= ft_strjoin(pipex_data->cmd_absolute_path[cmd_i],
			cmd_parameter[0][cmd_i]);
		cmd_i++;
	}
	pipex_data->cmd_absolute_path_with_parameter[cmd_i] = NULL;
}

void	get_cmd_absolute_path(char **argv, char **envp, t_pipex_data *pipex_data)
{
	char	**env_path;
	char	**cmd_parameter;

	// get_env_path(&env_path, envp);
env_path = ft_split("PATH=/Library/Frameworks/Python.framework/Versions/3.6/bin/:/Users/tobeshota/anaconda3/condabin/:/opt/homebrew/opt/node@18/bin/:/Users/tobeshota/.cargo/bin/:/usr/local/Qt-5.15.10/bin/:/opt/homebrew/opt/pyqt@5/5 5.15.7_2/bin/:/opt/homebrew/opt/qt@5/bin/:/Users/tobeshota/.nodebrew/current/bin/:/Users/tobeshota/.pyenv/shims/:/Users/tobeshota/.pyenv/bin/:/Library/Frameworks/Python.framework/Versions/3.10/bin/:/usr/local/bin/:/usr/bin/:/bin/:/usr/sbin/:/sbin/:/opt/X11/bin/:/Users/tobeshota/workspace/command", ':');
	get_cmd_name_from_arg(argv, &pipex_data->cmd_absolute_path);
	get_cmd_parameter(argv, &pipex_data->cmd_absolute_path, &cmd_parameter);
	add_absolute_path_to_cmd_name(&pipex_data->cmd_absolute_path, env_path, envp);
	get_cmd_absolute_path_with_parameter(argv, &cmd_parameter, pipex_data);
	all_free_tab(env_path);
	all_free_tab(cmd_parameter);
}
