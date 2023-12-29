/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_child.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 13:09:42 by toshota           #+#    #+#             */
/*   Updated: 2023/12/29 19:06:02 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "pipex.h"

bool	get_child(pid_t *child_pid)
{
	*child_pid = fork();
	if (check_fork(*child_pid) == false)
		return (false);
	return (true);
}

int	get_child_exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		if (g_in_cmd == SIG_INT_COMING)
			return (130);
		return (131);
	}
	else if (WIFSTOPPED(status))
		return (WSTOPSIG(status));
	return (0);
}
