/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:14:49 by toshota           #+#    #+#             */
/*   Updated: 2023/11/18 15:17:27 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	proc_here_doc(char *limitter, t_pipex_data *pipex_data)
{
	char	*line;
	char	*limitter_endl;

	pipex_data->infile_fd = open_file(HERE_DOC_FILE_PATH, INFILE_HERE_DOC);
	if (check_open(pipex_data->infile_fd) == FALSE)
		return (FALSE);
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
	if (check_close(close(pipex_data->infile_fd)) == FALSE)
		return (free(line), free(limitter_endl), FALSE);
	pipex_data->infile_fd = open_file(HERE_DOC_FILE_PATH, INFILE_HERE_DOC);
	if (check_open(pipex_data->infile_fd) == FALSE)
		return (free(line), free(limitter_endl), FALSE);
	return (free(line), free(limitter_endl), TRUE);
}
