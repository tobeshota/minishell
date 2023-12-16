/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 23:22:47 by toshota           #+#    #+#             */
/*   Updated: 2023/12/16 19:50:45 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#define ARG_IS_NOT_DETERMINED_WO_PATH -5

static bool	is_dir(char *file)
{
	struct stat	st;

	if (stat(file, &st) < 0 || is_match(file, ".."))
		return (false);
	return (S_ISDIR(st.st_mode));
}

static char	*get_argv_wo_param(char **argv, int arg_i)
{
	return (check_malloc \
	(ft_substr(argv[arg_i], 0, strlen_until_c(argv[arg_i], ' '))));
}

static int	is_false(char **argv, int arg_i)
{
	char	*argv_wo_param;
	char	*prev_argv_wo_param;

	argv_wo_param = get_argv_wo_param(argv, arg_i);
	if (is_specified_operators(argv_wo_param))
		return (free(argv_wo_param), true);
	if (arg_i > 0)
	{
		prev_argv_wo_param = get_argv_wo_param(argv, arg_i - 1);
		if (is_io_file(argv_wo_param, prev_argv_wo_param))
			return (free(argv_wo_param), free(prev_argv_wo_param), true);
		free(prev_argv_wo_param);
	}
	return (free(argv_wo_param), false);
}

static int	is_arg_determined_wo_path(char **argv, int arg_i, char **h_envp)
{
	if (is_match(*argv, "."))
		return (IS_DOT);
	if (is_dir(*argv))
		return (IS_A_DIRECTORY);
	if (is_file_exectable_wo_additional_path(*argv))
		return (true);
	if (is_false(argv, arg_i))
		return (false);
	if (getenv_from_h_envp(h_envp, "PATH") == NULL || \
	is_match(*argv, "..") || ft_strlen(*argv) == 0)
		return (NOT_FOUND);
	return (ARG_IS_NOT_DETERMINED_WO_PATH);
}

int	is_cmd(char **argv, int arg_i, char **h_envp)
{
	int		ret;
	char	**path;
	int		i;
	char	*tmp;

	ret = is_arg_determined_wo_path(argv, arg_i, h_envp);
	if (ret != ARG_IS_NOT_DETERMINED_WO_PATH)
		return (ret);
	path = check_malloc \
	(add_slash_eos(ft_split(getenv_from_h_envp(h_envp, "PATH"), ':')));
	i = -1;
	while (path[++i])
	{
		tmp = check_malloc(ft_strjoin(path[i], *argv));
		if (is_file_exectable(tmp) || free_tab(tmp))
			return (all_free_tab(path), free(tmp), true);
	}
	return (all_free_tab(path), NOT_FOUND);
}
