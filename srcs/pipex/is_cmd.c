/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 23:22:47 by toshota           #+#    #+#             */
/*   Updated: 2023/12/17 15:15:49 by toshota          ###   ########.fr       */
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

static int	is_false(char *cunnret_argv, char *prev_argv)
{
	char	*current_argv_wo_param;
	char	*prev_argv_wo_param;

	current_argv_wo_param = check_malloc(ft_substr(cunnret_argv, 0, strlen_until_c(cunnret_argv, ' ')));
	if (is_specified_operators(current_argv_wo_param))
		return (free(current_argv_wo_param), true);
	if (prev_argv)
	{
		prev_argv_wo_param = check_malloc(ft_substr(prev_argv, 0, strlen_until_c(prev_argv, ' ')));
		if (is_io_file(current_argv_wo_param, prev_argv_wo_param))
			return (free(current_argv_wo_param), free(prev_argv_wo_param), true);
		free(prev_argv_wo_param);
	}
	return (free(current_argv_wo_param), false);
}

static int	is_arg_determined_wo_path(char *cunnret_argv, char *prev_argv, char **h_envp)
{
	if (is_match(cunnret_argv, "."))
		return (IS_DOT);
	if (is_dir(cunnret_argv))
		return (IS_A_DIRECTORY);
	if (is_file_exectable_wo_additional_path(cunnret_argv))
		return (true);
	if (is_false(cunnret_argv, prev_argv))
		return (false);
	if (getenv_from_h_envp(h_envp, "PATH") == NULL || \
	is_match(cunnret_argv, "..") || ft_strlen(cunnret_argv) == 0)
		return (NOT_FOUND);
	return (ARG_IS_NOT_DETERMINED_WO_PATH);
}

int	is_cmd(char *cunnret_argv, char *prev_argv, char **h_envp)
{
	int		ret;
	char	**path;
	int		i;
	char	*tmp;

	ret = is_arg_determined_wo_path(cunnret_argv, prev_argv, h_envp);
	if (ret != ARG_IS_NOT_DETERMINED_WO_PATH)
		return (ret);
	path = check_malloc \
	(add_slash_eos(ft_split(getenv_from_h_envp(h_envp, "PATH"), ':')));
	i = -1;
	while (path[++i])
	{
		tmp = check_malloc(ft_strjoin(path[i], cunnret_argv));
		if (is_file_exectable(tmp) || free_tab(tmp))
			return (all_free_tab(path), free(tmp), true);
	}
	return (all_free_tab(path), NOT_FOUND);
}
