/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:14:49 by toshota           #+#    #+#             */
/*   Updated: 2023/11/18 00:22:53 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static void	wait_children(int cmd_i)
{
	int	i;

	i = 0;
	while (i < cmd_i)
	{
		check_wait(wait(NULL));
		i++;
	}
}

// 最初の文字が-だったらオプション[option]．そうでなければ引数[argment]ファイル
int is_parameter_arg(char *cmd_parameter)
{
	return (cmd_parameter[0] != '\0' && cmd_parameter[0] != '-' && is_file_exist(cmd_parameter));
}

int get_cmd_arg_fd(t_pipex_data *pipex_data, int cmd_i)
{
	int cmd_arg_fd;
	char *cmd_parameter;

	cmd_parameter = ft_substr(pipex_data->cmd_absolute_path_with_parameter[cmd_i], strlen_until_c(pipex_data->cmd_absolute_path_with_parameter[cmd_i], ' ')+1, ft_strlen(pipex_data->cmd_absolute_path_with_parameter[cmd_i]));
	check_malloc(cmd_parameter);
	if (is_parameter_arg(cmd_parameter))
		cmd_arg_fd = open_file(cmd_parameter, INFILE);
	else
		cmd_arg_fd = NOT_SPECIFIED;
	free(cmd_parameter);
	return cmd_arg_fd;
}

static void	set_input_fd(t_pipex_data *pipex_data, int cmd_i, char **argv)
{
	int cmd_arg_fd;

	get_infile_fd(pipex_data, cmd_i, argv);
	cmd_arg_fd = get_cmd_arg_fd(pipex_data, cmd_i);
	if (cmd_arg_fd != NOT_SPECIFIED)
	{
		check_dup(dup2(cmd_arg_fd, STDIN_FILENO));
		check_close(close(cmd_arg_fd));
	}
	// 入力先が指定されていない∧前にコマンドがある（cmd_iが0でない）場合にはパイプから読み取る
	if (is_fd_default(pipex_data->infile_fd, STDIN_FILENO) && cmd_i != 0)
	{
		check_dup(dup2(pipex_data->pipe_fd[cmd_i - 1][0], STDIN_FILENO));
		close_pipe(pipex_data->pipe_fd[cmd_i - 1]);
	}
	else
	{
		check_dup(dup2(pipex_data->infile_fd, STDIN_FILENO));
		check_close(close(pipex_data->infile_fd));
	}

}

static void	set_output_fd(t_pipex_data *pipex_data, int cmd_i, char **argv)
{
	get_outfile_fd(pipex_data, cmd_i, argv);
	// 出力先が指定されていない∧次にコマンドがある場合にはパイプにつなぐ
	if (is_fd_default(pipex_data->outfile_fd, STDOUT_FILENO) && pipex_data->cmd_absolute_path[cmd_i + 1] != NULL)
	{
		check_dup(dup2(pipex_data->pipe_fd[cmd_i][1], STDOUT_FILENO));
		close_pipe(pipex_data->pipe_fd[cmd_i]);
	}
	else if (!is_fd_default(pipex_data->outfile_fd, STDOUT_FILENO))
	{
		check_dup(dup2(pipex_data->outfile_fd, STDOUT_FILENO));
		check_close(close(pipex_data->outfile_fd));
	}
}

static void	exec_child(char **envp, t_pipex_data *pipex_data, int cmd_i, char **argv)
{
	char	**cmd;

	cmd = ft_split(pipex_data->cmd_absolute_path_with_parameter[cmd_i], ' ');
	check_malloc(cmd);
	set_input_fd(pipex_data, cmd_i, argv);
	set_output_fd(pipex_data, cmd_i, argv);
	check_execve(execve(pipex_data->cmd_absolute_path[cmd_i], cmd, envp));
}

void	do_pipe(char **envp, t_pipex_data *pipex_data, char **argv)
{
	int		cmd_i;
	pid_t	child_pid;

	cmd_i = 0;
	while (pipex_data->cmd_absolute_path[cmd_i])
	{
		get_pipe(pipex_data, cmd_i);
		child_pid = fork();
		check_fork(child_pid);
		if (child_pid == 0)
			exec_child(envp, pipex_data, cmd_i, argv);
		if (cmd_i > 0)
			close_pipe(pipex_data->pipe_fd[cmd_i - 1]);
		cmd_i++;
	}
	wait_children(cmd_i);
}
