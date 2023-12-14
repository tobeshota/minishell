/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:14:49 by toshota           #+#    #+#             */
/*   Updated: 2023/12/14 17:46:59 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "pipex.h"

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

	pipex->infile_fd = open_file(HERE_DOC_FILE_PATH, INFILE_HERE_DOC);
	if (check_open(pipex->infile_fd, "here_doc") == false)
		return (false);
	line = get_expanded_line(readline(HERE_DOC_PROMPT), h_envp, delimiter);
	delimiter_wo_quotas = omit_str(delimiter, "\'\"");
	while (is_match(line, delimiter_wo_quotas) == false && g_global.stop_heredoc == 0)
	{
		ft_putendl_fd(line, pipex->infile_fd);
		free(line);
		line = get_expanded_line(readline(HERE_DOC_PROMPT), h_envp, delimiter);
	}
	if (check_close(close(pipex->infile_fd)) == false || g_global.stop_heredoc == 1)
		return (free(line), free(delimiter_wo_quotas), false);
	pipex->infile_fd = open_file(HERE_DOC_FILE_PATH, INFILE_HERE_DOC);
	return (free(line), free(delimiter_wo_quotas), check_open(pipex->infile_fd,
			"here_doc"));
}

bool	proc_here_doc(char *delimiter, t_pipex *pipex, char **h_envp)
{
	pid_t	child_pid;
	int		cmd_num;

	cmd_num = 1;
	if (get_child(&child_pid) == false)
		return (false);
	if (child_pid == 0)
	{
		if (do_proc_here_doc(delimiter, pipex, h_envp) == false)
			return exit(1), false;
		return exit(0), true;
	}
	return (wait_children(cmd_num));
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
