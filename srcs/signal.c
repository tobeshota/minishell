/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 09:57:45 by yoshimurahi       #+#    #+#             */
/*   Updated: 2023/12/16 16:50:41 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	if (in_cmd == IF_HEREDOC)
	{
		g_global.error_num = 1;
		exit(1);
		return ;
	}
	else if(in_cmd == IN_CMD)
	{
		ft_printf("\n");
		rl_replace_line("", 0);
		rl_redisplay();
		return ;
	}
	else if(in_cmd == HEREDOC_PARENT_CASE)
	{
		ft_printf("\n");
		return ;
	}
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void)sig;
}

void	sigquit_handler(int sig)
{
	ft_putstr_fd("Quit: ", STDERR_FILENO);
	ft_putnbr_fd(sig, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

void	signal_init_main(t_tools *tools)
{
	if (in_cmd == SIGINT)
	{
		g_global.error_num = 130;
		tools->error_num = 130;
	}
	else if(in_cmd == SIGQUIT)
	{
		g_global.error_num = 131;
		tools->error_num = 131;
	}
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
