/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 23:22:47 by toshota           #+#    #+#             */
/*   Updated: 2023/12/05 09:12:38 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static bool	is_specified_redirect(char *str)
{
	return (is_specified_infile(str) || is_specified_here_doc(str)
		|| is_specified_outfile_overwriting(str)
		|| is_specified_outfile_apend(str));
}

static bool	is_io_file(char **argv, int arg_i)
{
	return (arg_i > 0 && is_specified_redirect(argv[arg_i - 1]) && argv[arg_i]);
}

static bool	is_file_with_path(char *str)
{
	return (ft_strchr(str, '/'));
}

int	is_cmd(char **argv, int arg_i)
{
	char	*argv_wo_param;
	char	**path;
	int		i;
	char	*tmp;

	argv_wo_param = check_malloc(ft_substr(argv[arg_i], 0,
				strlen_until_c(argv[arg_i], ' ')));
	if (is_cmd_builtin(argv_wo_param) \
	|| (is_file_exectable(argv_wo_param) && is_file_with_path(argv_wo_param)))
		return (free(argv_wo_param), true);
	else if (is_specified_operators(argv[arg_i]) || is_io_file(argv, arg_i) \
	|| getenv("PATH") == NULL)
		return (free(argv_wo_param), false);
	path = check_malloc(add_slash_eos(ft_split(getenv("PATH"), ':')));
	i = -1;
	while (path[++i])
	{
		tmp = check_malloc(ft_strjoin(path[i], argv_wo_param));
		if (is_file_exectable(tmp) == true)
			break ;
		free(tmp);
	}
	if (path[i] == NULL)
		return (all_free_tab(path), free(argv_wo_param), NOT_FOUND);
	return (all_free_tab(path), free(tmp), free(argv_wo_param), true);
}
