/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:14:49 by toshota           #+#    #+#             */
/*   Updated: 2023/12/10 21:07:48 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool	proc_here_doc(char *limitter, t_pipex *pipex)
{
	char	*line;

	pipex->infile_fd = open_file(HERE_DOC_FILE_PATH, INFILE_HERE_DOC);
	if (check_open(pipex->infile_fd, "here_doc") == false)
		return (false);
	line = readline(HERE_DOC_PROMPT);
	while (is_match(line, limitter) == false)
	{
		ft_putendl_fd(line, pipex->infile_fd);
		free(line);
		line = readline(HERE_DOC_PROMPT);
	}
	if (check_close(close(pipex->infile_fd)) == false)
		return (free(line), false);
	pipex->infile_fd = open_file(HERE_DOC_FILE_PATH, INFILE_HERE_DOC);
	return (free(line), check_open(pipex->infile_fd, "here_doc"));
}

bool	rm_here_doc(void)
{
	if (is_file_exist(HERE_DOC_FILE_PATH))
	{
		if (check_unlink(unlink(HERE_DOC_FILE_PATH)) == false)
			return (false);
	}
	return (true);
}
