/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:14:49 by toshota           #+#    #+#             */
/*   Updated: 2023/11/20 10:50:56 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	check_is_limitter_specified(char *limitter)
{
	if (limitter == NULL)
	{
		put_error("-bash: syntax error near unexpected token `newline'\n");
		return (false);
	}
	return (true);
}

int	proc_here_doc(char *limitter, t_pipex_data *pipex_data)
{
	char	*line;
	char	*limitter_endl;

	if (check_is_limitter_specified(limitter) == false)
		return (false);
	pipex_data->infile_fd = open_file(HERE_DOC_FILE_PATH, INFILE_HERE_DOC);
	if (check_open(pipex_data->infile_fd) == false)
		return (false);
	ft_printf("> ");
	line = get_next_line(STDIN_FILENO);
	limitter_endl = check_malloc(ft_strjoin(limitter, "\n"));
	while (ft_strncmp(line, limitter_endl, ft_strlen(line)))
	{
		ft_putstr_fd(line, pipex_data->infile_fd);
		free(line);
		ft_printf("> ");
		line = get_next_line(STDIN_FILENO);
	}
	if (check_close(close(pipex_data->infile_fd)) == false)
		return (free(line), free(limitter_endl), false);
	pipex_data->infile_fd = open_file(HERE_DOC_FILE_PATH, INFILE_HERE_DOC);
	if (check_open(pipex_data->infile_fd) == false)
		return (free(line), free(limitter_endl), false);
	return (free(line), free(limitter_endl), true);
}
