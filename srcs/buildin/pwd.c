/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:39:21 by toshota           #+#    #+#             */
/*   Updated: 2023/11/20 11:49:42 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildin.h"

int	pwd(char **envp)
{
	char	**pwd;

	if (get_pwd(&pwd, envp) == false)
		return (false);
	write(STDIN_FILENO, pwd[0], ft_strlen(pwd[0]) - 1);
	ft_putchar_fd('\n', STDIN_FILENO);
	all_free_tab(pwd);
	return true;
}
