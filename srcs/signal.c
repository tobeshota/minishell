/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshimurahiro <yoshimurahiro@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 09:57:45 by yoshimurahi       #+#    #+#             */
/*   Updated: 2023/12/13 10:00:06 by yoshimurahi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	g_global.error_num = 130;
	if (!g_global.in_heredoc)
		ft_putstr_fd("\n", STDERR_FILENO);
	rm_here_doc();
	if (g_global.in_cmd)
	{
		g_global.stop_heredoc = 1;
		rl_redisplay();
		return ;
	}
	rl_on_new_line();
	rl_redisplay();
	(void)sig;
}

void	sigquit_handler(int sig)
{
	g_global.error_num = 131;
	ft_putstr_fd("Quit: ", STDERR_FILENO);
	ft_putnbr_fd(sig, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

void	signal_init(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
