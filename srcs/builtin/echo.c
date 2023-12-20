/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:39:21 by toshota           #+#    #+#             */
/*   Updated: 2023/12/20 21:24:39 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	ft_putstr_fd_w_space_except_last(char **cmd, int cmd_i,
		t_pipex *pipex)
{
	ft_putstr_fd(cmd[cmd_i], pipex->outfile_fd);
	if (cmd[cmd_i + 1])
		ft_putchar_fd(' ', pipex->outfile_fd);
}

static bool	is_optin_specified(char *option, char option_name)
{
	int	i;

	if (option == NULL)
		return (false);
	if (option[0] != '-')
		return (false);
	if (option[1] != option_name)
		return (false);
	i = 2;
	while (option[i] && option[i] == option_name)
		i++;
	return (option[i] == '\0');
}

static void	skip_option(char **cmd, int *cmd_i)
{
	while (is_optin_specified(cmd[*cmd_i], 'n') == true)
		(*cmd_i)++;
}

int	exec_echo(char **cmd, t_pipex *pipex)
{
	int	cmd_i;

	cmd_i = 1;
	skip_option(cmd, &cmd_i);
	while (cmd[cmd_i])
	{
		ft_putstr_fd_w_space_except_last(cmd, cmd_i, pipex);
		cmd_i++;
	}
	if (is_optin_specified(cmd[1], 'n') == false)
		ft_putchar_fd('\n', pipex->outfile_fd);
	return (true);
}
