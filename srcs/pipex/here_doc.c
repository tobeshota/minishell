/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:14:49 by toshota           #+#    #+#             */
/*   Updated: 2023/12/06 13:56:39 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	check_is_limitter_specified(char *limitter)
{
	if (limitter == NULL)
	{
		put_error("-minishell: syntax error near unexpected token `newline'\n");
		return (false);
	}
	return (true);
}

#include "minishell.h"
bool	proc_here_doc(char *limitter, t_pipex *pipex)
{
	char	*line;
	char	*limitter_endl;

	if (check_is_limitter_specified(limitter) == false)
		return (false);
	pipex->infile_fd = open_file(HERE_DOC_FILE_PATH, INFILE_HERE_DOC);
	if (check_open(pipex->infile_fd, "here_doc") == false)
		return (false);
	ft_printf("> ");
	// line = expander(tools, check_malloc(ft_split(get_next_line(STDIN_FILENO), '\0')));
	line = get_next_line(STDIN_FILENO);
	limitter_endl = check_malloc(ft_strjoin(limitter, "\n"));
	while (ft_strncmp(line, limitter_endl, ft_strlen(line)))
	{
		ft_putstr_fd(line, pipex->infile_fd);
		free(line);
		ft_printf("> ");
		line = get_next_line(STDIN_FILENO);
	}
	if (check_close(close(pipex->infile_fd)) == false)
		return (free(line), free(limitter_endl), false);
	pipex->infile_fd = open_file(HERE_DOC_FILE_PATH, INFILE_HERE_DOC);
	if (check_open(pipex->infile_fd, "here_doc") == false)
		return (free(line), free(limitter_endl), false);
	return (free(line), free(limitter_endl), true);
}
