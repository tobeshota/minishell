/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_count.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 09:00:12 by toshota           #+#    #+#             */
/*   Updated: 2023/12/05 10:59:43 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* "."や".."や"../"が指定されたときの対応をする！ */
int	get_cmd_count(char **argv)
{
	int		cmd_count;
	int		arg_i;
	int		ret;
	char	*argv_wo_param;

	cmd_count = 0;
	arg_i = 0;
	while (argv[arg_i])
	{
		argv_wo_param = check_malloc \
		(ft_substr(argv[arg_i], 0, strlen_until_c(argv[arg_i], ' ')));
		ret = is_cmd(argv, arg_i);
		if (ret == true)
			cmd_count++;
		else if (ret == NOT_FOUND)
			put_error_with_filename(argv_wo_param, "command not found");
		arg_i++;
		free(argv_wo_param);
	}
	return (cmd_count);
}
