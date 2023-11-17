/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pipex_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:51:21 by toshota           #+#    #+#             */
/*   Updated: 2023/10/31 15:14:19 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	get_cmd_count(char **argv)
{
	int	cmd_count;
	int	arg_i;

	cmd_count = 0;
	arg_i = 0;
	while (argv[arg_i])
	{
		if (is_cmd(argv, arg_i))
			cmd_count++;
		arg_i++;
	}
	return (cmd_count);
}

int get_start_pos(int pipe_count, char **argv)
{
	int arg_i;

	arg_i = 0;
	while(argv[arg_i] && pipe_count)
	{
		if (is_specified_pipe(argv[arg_i]))
			pipe_count--;
		arg_i++;
	}
	return arg_i;
}

// < の次のファイルを infile とする
// << が来たら標準入力を求め，それを/tmp/here_docに格納する
// << と < が両方来た場合には，来た順番から/tmp/here_docに追記していく？
void	get_infile_fd(t_pipex_data *pipex_data, int cmd_i, char **argv)
{
	int arg_i;

	arg_i = get_start_pos(cmd_i, argv);
	pipex_data->infile_fd = STDIN_FILENO;
	while(argv[arg_i] && !is_specified_pipe(argv[arg_i]))
	{
		if (is_specified_infile(argv[arg_i]))
			pipex_data->infile_fd = open_file(argv[arg_i+1], INFILE);
		else if (is_specified_here_doc(argv[arg_i]))
			proc_here_doc(argv[arg_i+1], pipex_data);
		arg_i++;
	}
}

void	get_outfile_fd(t_pipex_data *pipex_data, int cmd_i, char **argv)
{
	int arg_i;

	arg_i = get_start_pos(cmd_i, argv);
	pipex_data->outfile_fd = STDOUT_FILENO;
	while(argv[arg_i] && !is_specified_pipe(argv[arg_i]))
	{
		if (is_specified_outfile_overwriting(argv[arg_i]))
			pipex_data->outfile_fd = open_file(argv[arg_i+1], OUTFILE_OVER_WRITING);
		else if (is_specified_outfile_apend(argv[arg_i]))
			pipex_data->outfile_fd = open_file(argv[arg_i+1], OUTFILE_APEND);
		arg_i++;
	}
}

static void	malloc_multiple_pipe(int argc, char **argv, t_pipex_data *pipex_data)
{
	int	i;

	i = argc - argc;
	pipex_data->pipe_fd = (int **)malloc(sizeof(int *) * (get_cmd_count(argv)
				+ 1));
	check_malloc(pipex_data->pipe_fd);
	while (i < get_cmd_count(argv))
	{
		pipex_data->pipe_fd[i] = (int *)malloc(sizeof(int) * 2);
		check_malloc(pipex_data->pipe_fd);
		i++;
	}
	pipex_data->pipe_fd[i] = NULL;
}

void	get_pipex_data(int argc, char **argv, char **envp, t_pipex_data *pipex_data)
{
	get_cmd_absolute_path(argv, envp, pipex_data);
	malloc_multiple_pipe(argc, argv, pipex_data);
}
