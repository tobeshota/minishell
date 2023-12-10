/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:14:49 by toshota           #+#    #+#             */
/*   Updated: 2023/12/10 22:07:47 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_expanded_line(char *line, char **heap_envp)
{
	char	*tmp;

	if (line == NULL || line[0] == '\0')
		return (line);
	if (find_dollar(line) && line[find_dollar(line) - 2] != '\''
		&& line[find_dollar(line)])
	{
		tmp = detect_dollar(line, heap_envp);
		free(line);
		line = tmp;
	}
	if (ft_strncmp(line, "export", ft_strlen(line) - 1) != 0)
	{
		line = delete_quotes(line, '\"');
		line = delete_quotes(line, '\'');
	}
	return (line);
}

bool	proc_here_doc(char *limitter, t_pipex *pipex, char **heap_envp)
{
	char	*line;

	pipex->infile_fd = open_file(HERE_DOC_FILE_PATH, INFILE_HERE_DOC);
	if (check_open(pipex->infile_fd, "here_doc") == false)
		return (false);
	line = get_expanded_line(readline(HERE_DOC_PROMPT), heap_envp);
	while (is_match(line, limitter) == false)
	{
		ft_putendl_fd(line, pipex->infile_fd);
		free(line);
		line = get_expanded_line(readline(HERE_DOC_PROMPT), heap_envp);
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
