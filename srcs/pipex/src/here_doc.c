/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:14:49 by toshota           #+#    #+#             */
/*   Updated: 2023/11/18 00:58:55 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	proc_here_doc(char *limitter, t_pipex_data *pipex_data)
{
	char	*line;
	char	*limitter_endl;

	pipex_data->infile_fd = open_file(HERE_DOC_FILE_PATH, INFILE_HERE_DOC);
	ft_printf("> ");
	line = get_next_line(STDIN_FILENO);
	limitter_endl = ft_strjoin(limitter, "\n");
	check_malloc(limitter_endl);
	while (ft_strncmp(line, limitter_endl, ft_strlen(line)))
	{
		ft_putstr_fd(line, pipex_data->infile_fd);
		free(line);
		ft_printf("> ");
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	free(limitter_endl);
	check_close(close(pipex_data->infile_fd));
	pipex_data->infile_fd = open_file(HERE_DOC_FILE_PATH, INFILE_HERE_DOC);
}
