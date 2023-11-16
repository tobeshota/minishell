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

int	get_cmd_count(int argc, char **argv)
{
	int	cmd_count;
	int	arg_i;

	cmd_count = 0;
	arg_i = 0;
	// if (is_specified_here_doc(argv))
	// 	arg_i = 3;
	// else
	// 	arg_i = 2;
	while (argv[arg_i])
	{
		if (is_cmd(argv[arg_i]))
			cmd_count++;
		arg_i++;
	}
	return (cmd_count);
}

// < の次のファイルを infile とする
// << が来たら標準入力を求め，それを/tmp/here_docに格納する
// << と < が両方来た場合には，来た順番から/tmp/here_docに追記していく？
static void	get_infile_fd(char **argv, t_pipex_data *pipex_data)
{
	int arg_i;

	arg_i = 0;
	pipex_data->infile_fd = STDIN_FILENO;
	while(argv[arg_i])
	{
		if (is_specified_infile(argv[arg_i]))
			pipex_data->infile_fd = open_file(argv[arg_i+1], INFILE);
		else if (is_specified_here_doc(argv[arg_i]))
			proc_here_doc(argv[arg_i+1], pipex_data->infile_fd);
		arg_i++;
	}
	// if (get_infile(argv))
	// {
	// 	*infile_fd = open_file(HERE_DOC_FILE_PATH, INFILE_HERE_DOC);
	// 	proc_here_doc(argv[2], *infile_fd);
	// }
	// else
	// 	*infile_fd = open_file(get_infile(argv), INFILE);
}

static void	get_outfile_fd(char **argv, t_pipex_data *pipex_data)
{
	int arg_i;

	arg_i = 0;
	pipex_data->outfile_fd = STDOUT_FILENO;
	while(argv[arg_i])
	{
		if (is_specified_outfile_overwriting(argv[arg_i]))
			pipex_data->outfile_fd = open_file(argv[arg_i+1], OUTFILE_OVER_WRITING);
		else if (is_specified_outfile_apend(argv[arg_i]))
			pipex_data->outfile_fd = open_file(argv[arg_i], OUTFILE_APEND);
		arg_i++;
	}
	// if (is_specified_here_doc(argv))
	// 	*outfile_fd = open_file(get_outfile(argv), OUTFILE_APEND);
	// else
	// 	*outfile_fd = open_file(get_outfile(argv), OUTFILE_OVER_WRITING);
}

static void	malloc_multiple_pipe(int argc, char **argv, t_pipex_data *pipex_data)
{
	int	i;

	i = 0;
	pipex_data->pipe_fd = (int **)malloc(sizeof(int *) * (get_cmd_count(argc, argv)
				+ 1));
	check_malloc(pipex_data->pipe_fd);
	while (i < get_cmd_count(argc, argv))
	{
		pipex_data->pipe_fd[i] = (int *)malloc(sizeof(int) * 2);
		check_malloc(pipex_data->pipe_fd);
		i++;
	}
	pipex_data->pipe_fd[i] = NULL;
}

void	get_pipex_data(int argc, char **argv, char **envp, t_pipex_data *pipex_data)
{
	get_infile_fd(argv, pipex_data);
	get_outfile_fd(argv, pipex_data);
	get_cmd_absolute_path(argc, argv, envp, pipex_data);
	malloc_multiple_pipe(argc, argv, pipex_data);
}
