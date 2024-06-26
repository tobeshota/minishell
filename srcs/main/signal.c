/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 09:57:45 by yoshimurahi       #+#    #+#             */
/*   Updated: 2023/12/19 13:06:52 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	if (g_in_cmd == IF_HEREDOC)
	{
		exit(1);
		g_in_cmd = SIG_INT_COMING;
		return ;
	}
	else if (g_in_cmd == IN_CMD)
	{
		ft_printf("\n");
		rl_replace_line("", 0);
		rl_redisplay();
		g_in_cmd = SIG_INT_COMING;
		return ;
	}
	else if (g_in_cmd == HEREDOC_PARENT_CASE)
	{
		ft_printf("\n");
		g_in_cmd = SIG_INT_COMING;
		return ;
	}
	g_in_cmd = SIG_INT_COMING;
	(void)sig;
	return (ft_printf("\n"), rl_on_new_line(), rl_replace_line("", 0),
		rl_redisplay());
}

void	sigquit_handler(int sig)
{
	ft_putstr_fd("Quit: ", STDERR_FILENO);
	ft_putnbr_fd(sig, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

void	signal_init_main(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
