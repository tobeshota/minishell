/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 20:47:06 by toshota           #+#    #+#             */
/*   Updated: 2023/12/05 20:48:45 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	put_error(char *err_msg)
{
	write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
}

void	put_error_w_cmd(char *cmd, char *error_msg)
{
	put_error("-minishell: ");
	put_error(cmd);
	put_error(": ");
	put_error(error_msg);
	put_error("\n");
}

void	put_error_w_cmd_filename(char *cmd, char *file,
		char *error_msg)
{
	g_global.error_num = 1;
	if (file == NULL)
		return put_error_w_cmd(cmd, error_msg);
	else
	{
		put_error("-minishell: ");
		put_error(cmd);
		put_error(": ");
		put_error(file);
		put_error(": ");
		put_error(error_msg);
		put_error("\n");
	}
}

int put_file_error(char *cmd, char *file)
{
	if(errno == 0)
		return true;
	return put_error_w_cmd_filename(cmd, file, strerror(errno)), false;
}
