/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:14:49 by toshota           #+#    #+#             */
/*   Updated: 2023/12/15 09:53:54 by toshota          ###   ########.fr       */
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

static char	*get_expanded_line(char *line, char **h_envp, char *delimiter)
{
	char	*tmp;

	if (line == NULL || line[0] == '\0' || is_surrounded_by_quotas(delimiter))
		return (line);
	if (find_dollar(line) && line[find_dollar(line) - 2] != '\''
		&& line[find_dollar(line)])
	{
		tmp = detect_dollar(line, h_envp);
		free(line);
		line = tmp;
	}
	return (line);
}

bool	do_proc_here_doc(char *delimiter, t_pipex *pipex, char **h_envp)
{
	char	*line;
	char	*delimiter_wo_quotas;

	line = get_expanded_line(readline(HERE_DOC_PROMPT), h_envp, delimiter);
	delimiter_wo_quotas = omit_str(delimiter, "\'\"");
	while (is_match(line, delimiter_wo_quotas) == false)
	{
		ft_putendl_fd(line, pipex->infile_fd);
		free(line);
		line = get_expanded_line(readline(HERE_DOC_PROMPT), h_envp, delimiter);
	}
	return (free(line), free(delimiter_wo_quotas), true);
}

bool	proc_here_doc(char *delimiter, t_pipex *pipex, char **h_envp)
{
	pid_t	child_pid;

	pipex->infile_fd = open_file(HERE_DOC_FILE_PATH, INFILE_HERE_DOC);
	if (check_open(pipex->infile_fd, "here_doc") == false)
		return (false);
	if (get_child(&child_pid) == false)
		return (false);
	if (child_pid == 0)
	{
		do_proc_here_doc(delimiter, pipex, h_envp);
		exit(0);
	}
	else
	{
		g_global.in_cmd = 0;
		if (check_close(close(pipex->infile_fd)) == false)
			return (false);
		pipex->infile_fd = open_file(HERE_DOC_FILE_PATH, INFILE_HERE_DOC);
		if (check_open(pipex->infile_fd, "here_doc") == false)
			return (false);
		return (wait_children(CHILD_NUM));
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
