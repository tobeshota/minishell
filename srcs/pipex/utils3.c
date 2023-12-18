/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 00:14:56 by toshota           #+#    #+#             */
/*   Updated: 2023/12/19 00:17:58 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*double_to_sigle(char **array, char splitter)
{
	char	*str;
	char	splitter_str[2];
	char	*tmp;
	int		i;

	str = NULL;
	splitter_str[0] = splitter;
	splitter_str[1] = '\0';
	i = 0;
	while (array[i])
	{
		tmp = str;
		str = check_malloc(ft_strjoin(str, array[i]));
		free(tmp);
		if (array[i + 1])
		{
			tmp = str;
			str = check_malloc(ft_strjoin(str, splitter_str));
			free(tmp);
		}
		i++;
	}
	return (str);
}

bool	check_is_dir(char *filename, int ret, t_pipex *pipex)
{
	if (ret == IS_A_DIRECTORY)
	{
		put_error_w_cmd(filename, "is a directory");
		*pipex->error_num = 126;
		return (false);
	}
	return (true);
}

bool	check_cmd_exist(char *filename, int ret, t_pipex *pipex)
{
	if (ret == NOT_FOUND)
	{
		put_error_w_cmd(filename, "command not found");
		*pipex->error_num = 127;
		return (false);
	}
	return (true);
}

bool	check_is_dot(int ret, t_pipex *pipex)
{
	if (ret == IS_DOT)
	{
		put_error("minishell: .: filename argument required\n.\
		: usage: . filename [arguments]\n");
		*pipex->error_num = 2;
		return (false);
	}
	return (true);
}
