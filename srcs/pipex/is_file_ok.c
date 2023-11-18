/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_file_ok.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:14:49 by toshota           #+#    #+#             */
/*   Updated: 2023/11/18 16:16:28 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	is_file_exist(char *file)
{
	return (!access(file, F_OK));
}

int	is_file_readable(char *file)
{
	return (!access(file, R_OK));
}

int	is_file_writable(char *file)
{
	return (!access(file, W_OK));
}

int	is_file_exectable(char *file)
{
	return (!access(file, X_OK));
}
