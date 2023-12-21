/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjia <cjia@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:14:49 by toshota           #+#    #+#             */
/*   Updated: 2023/12/21 10:34:49 by cjia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "pipex.h"
#define CHILD_NUM 1

static int	is_delimiter_included_encloser(char *delimiter)
{
	return (ft_strchr(delimiter, '\'') || ft_strchr(delimiter, '\"'));
}

static char	*get_expanded_line(char *line, char **h_envp, char *delimiter,
		t_tools *tools)
{
	char	*tmp;

	if (line == NULL || line[0] == '\0' || \
	is_delimiter_included_encloser(delimiter) || is_match(line, delimiter))
		return (line);
	if (find_dollar(line) && line[find_dollar(line) - 2] != '\''
		&& line[find_dollar(line)])
	{
		tmp = process_dollar_quote(line, h_envp, tools);
		free(line);
		line = tmp;
	}
	return (line);
}

static int	do_proc_here_doc(char *delimiter, t_pipex *pipex, char **h_envp,
		t_tools *tools)
{
	char	*line;
	char	*delimiter_wo_quotas;

	g_in_cmd = IF_HEREDOC;
	line = get_expanded_line \
	(readline(HERE_DOC_PROMPT), h_envp, delimiter, tools);
	delimiter_wo_quotas = omit_str(delimiter, "\'\"");
	while (line && is_match(line, delimiter_wo_quotas) == false)
	{
		ft_putendl_fd(line, pipex->infile_fd);
		free(line);
		line = get_expanded_line \
		(readline(HERE_DOC_PROMPT), h_envp, delimiter, tools);
	}
	return (free(line), free(delimiter_wo_quotas), 0);
}

bool	proc_here_doc(char *delimiter, t_pipex *pipex, char **h_envp,
		t_tools *tools)
{
	pid_t	child_pid;

	if (rm_here_doc() == false)
		return (false);
	pipex->infile_fd = open_file(HERE_DOC_FILE_PATH, INFILE_HERE_DOC);
	if (check_open(pipex->infile_fd, "here_doc", pipex) == false)
		return (false);
	if (get_child(&child_pid) == false)
		return (false);
	if (child_pid == 0)
		exit(do_proc_here_doc(delimiter, pipex, h_envp, tools));
	else
	{
		g_in_cmd = HEREDOC_PARENT_CASE;
		if (check_close(close(pipex->infile_fd)) == false)
			return (false);
		pipex->infile_fd = open_file(HERE_DOC_FILE_PATH, INFILE_HERE_DOC);
		if (check_open(pipex->infile_fd, "here_doc", pipex) == false)
			return (false);
		waitpid(child_pid, NULL, 0);
		return (true);
	}
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
