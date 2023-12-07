/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 23:22:47 by toshota           #+#    #+#             */
/*   Updated: 2023/12/07 13:26:41 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static bool	is_dir(char *file)
{
	struct stat	st;

	if (stat(file, &st) < 0 || is_match(file, ".."))
		return (false);
	return (S_ISDIR(st.st_mode));
}

static int	is_file_exectable_wo_additional_path(char *file)
{
	return (is_cmd_builtin(file) \
	|| (is_file_exectable(file) && ft_strchr(file, '/')));
}

static int	is_false(char **argv, int arg_i)
{
	return (is_specified_operators(argv[arg_i]) || is_io_file(argv, arg_i) \
	|| getenv("PATH") == NULL);
}

int	is_cmd(char **argv, int arg_i)
{
	char	*argv_wo_param;
	char	**path;
	int		i;
	char	*tmp;

	argv_wo_param = check_malloc \
	(ft_substr(argv[arg_i], 0, strlen_until_c(argv[arg_i], ' ')));
	if (is_match(argv_wo_param, "."))
		return (free(argv_wo_param), IS_DOT);
	else if (is_dir(argv_wo_param))
		return (free(argv_wo_param), IS_A_DIRECTORY);
	else if (is_file_exectable_wo_additional_path(argv_wo_param))
		return (free(argv_wo_param), true);
	else if (is_false(argv, arg_i))
		return (free(argv_wo_param), false);
	path = check_malloc(add_slash_eos(ft_split(getenv("PATH"), ':')));
	i = -1;
	while (path[++i])
	{
		tmp = check_malloc(ft_strjoin(path[i], argv_wo_param));
		if (is_file_exectable(tmp) && !is_match(argv_wo_param, ".."))
			return (all_free_tab(path), free(argv_wo_param), free(tmp), true);
		free(tmp);
	}
	return (all_free_tab(path), free(argv_wo_param), NOT_FOUND);
}
