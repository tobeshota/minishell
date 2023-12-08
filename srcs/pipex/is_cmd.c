/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 23:22:47 by toshota           #+#    #+#             */
/*   Updated: 2023/12/08 21:25:46 by toshota          ###   ########.fr       */
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
	return (is_specified_operators(argv[arg_i]) || is_io_file(argv, arg_i));
}

static char	*get_argv_wo_param(char **argv, int arg_i)
{
	return (check_malloc \
	(ft_substr(argv[arg_i], 0, strlen_until_c(argv[arg_i], ' '))));
}

int	is_cmd(char **argv, int arg_i, char **heap_envp)
{
	char	*argv_wo_param;
	char	**path;
	int		i;
	char	*tmp;

	argv_wo_param = get_argv_wo_param(argv, arg_i);
	if (is_match(argv_wo_param, "."))
		return (free_tab(argv_wo_param), IS_DOT);
	else if (is_dir(argv_wo_param))
		return (free_tab(argv_wo_param), IS_A_DIRECTORY);
	else if (is_file_exectable_wo_additional_path(argv_wo_param))
		return (free_tab(argv_wo_param), true);
	else if (is_false(argv, arg_i))
		return (free_tab(argv_wo_param), false);
	else if (getenv_from_heap_envp(heap_envp, "PATH") == NULL
		|| is_match(argv_wo_param, ".."))
		return (free_tab(argv_wo_param), NOT_FOUND);
	path = check_malloc \
	(add_slash_eos(ft_split(getenv_from_heap_envp(heap_envp, "PATH"), ':')));
	i = -1;
	while (path[++i])
	{
		tmp = check_malloc(ft_strjoin(path[i], argv_wo_param));
		if (is_file_exectable(tmp) || free_tab(tmp))
			return (all_free_tab(path), free(argv_wo_param), free(tmp), true);
	}
	return (all_free_tab(path), free_tab(argv_wo_param), NOT_FOUND);
}
