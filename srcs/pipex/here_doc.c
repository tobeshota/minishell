/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:14:49 by toshota           #+#    #+#             */
/*   Updated: 2023/12/18 15:02:47 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "pipex.h"
#define CHILD_NUM 1

static int	is_surrounded_by_quotas(char *str)
{
	char	bos;
	char	eos;

	bos = str[0];
	eos = str[ft_strlen(str) - 1];
	if (bos == '\'' && eos == '\'' && bos == eos)
		return (true);
	else if (bos == '\"' && eos == '\"' && bos == eos)
		return (true);
	return (false);
}

static char	*get_expanded_line(char *line, char **h_envp, char *delimiter, t_tools *tools)
{
	char	*tmp;

	if (line == NULL || line[0] == '\0' || \
	is_surrounded_by_quotas(delimiter) || is_match(line, delimiter))
		return (line);
	if (find_dollar(line) && line[find_dollar(line) - 2] != '\''
		&& line[find_dollar(line)])
	{
		tmp = detect_dollar(line, h_envp, tools);
		free(line);
		line = tmp;
	}
	return (line);
}

static bool	do_proc_here_doc(char *delimiter, t_pipex *pipex, char **h_envp, t_tools *tools)
{
	char	*line;
	char	*delimiter_wo_quotas;

	in_cmd = IF_HEREDOC;
	line = get_expanded_line \
	(readline(HERE_DOC_PROMPT), h_envp, delimiter, tools);
	delimiter_wo_quotas = omit_str(delimiter, "\'\"");
	while (is_match(line, delimiter_wo_quotas) == false)
	{
		ft_putendl_fd(line, pipex->infile_fd);
		free(line);
		line = get_expanded_line \
		(readline(HERE_DOC_PROMPT), h_envp, delimiter, tools);
	}
	return (free(line), free(delimiter_wo_quotas), true);
}

bool	proc_here_doc(char *delimiter, t_pipex *pipex, char **h_envp, t_tools *tools)
{
	pid_t	child_pid;

	pipex->infile_fd = open_file(HERE_DOC_FILE_PATH, INFILE_HERE_DOC);
	if (check_open(pipex->infile_fd, "here_doc", pipex) == false)
		return (false);
	if (get_child(&child_pid) == false)
		return (false);
	if (child_pid == 0)
	{
		do_proc_here_doc(delimiter, pipex, h_envp, tools);
		exit(0);
	}
	else
	{
		in_cmd = HEREDOC_PARENT_CASE;
		if (check_close(close(pipex->infile_fd)) == false)
			return (false);
		pipex->infile_fd = open_file(HERE_DOC_FILE_PATH, INFILE_HERE_DOC);
		if (check_open(pipex->infile_fd, "here_doc", pipex) == false)
			return (false);
		return (wait_children(CHILD_NUM, pipex));
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
