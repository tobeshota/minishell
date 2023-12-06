/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:14:49 by toshota           #+#    #+#             */
/*   Updated: 2023/12/04 23:22:46 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool	is_cmd_relative_path(char ***cmd_absolute_path, int cmd_i)
{
	return (cmd_absolute_path[0][cmd_i][0] != '/'
		&& ft_strchr(&cmd_absolute_path[0][cmd_i][1], '/'));
}

bool	is_cmd_alreadly_absollute_path(char ***cmd_absolute_path, int cmd_i)
{
	return (cmd_absolute_path[0][cmd_i][0] == '/'
		&& ft_strchr(&cmd_absolute_path[0][cmd_i][1], '/'));
}
