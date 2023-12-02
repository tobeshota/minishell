/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshimurahiro <yoshimurahiro@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 09:57:45 by yoshimurahi       #+#    #+#             */
/*   Updated: 2023/12/02 14:04:44 by yoshimurahi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_simple_cmdsclear(t_simple_cmds **lst)
{
	t_simple_cmds	*tmp;
	t_lexer			*redirections_tmp;

	if (!*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		redirections_tmp = (*lst)->redirections;
		ft_lexerclear(&redirections_tmp);
		if ((*lst)->str)
			free_arr((*lst)->str);
		if ((*lst)->file_name)
			free((*lst)->file_name);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}


// void	signal_handler_sigint(int signum)
// {
// 	(void)signum;
    
// 	// frag = SIGINT;
// 	ft_printf("\n");
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// }

// void	signal_handler_sigquit(int signum)
// {
// 	(void)signum;
// 	rl_on_new_line();
// 	rl_redisplay();
// }

// void	signal_init(void)
// {
// 	struct sigaction	sa1;
// 	struct sigaction	sa2;

// 	// if (frag == 1 || frag == SIGINT)
// 	// 	data->exit_status = 1;
// 	// frag = 0;
// 	sigemptyset(&sa1.sa_mask);
// 	sa1.sa_sigaction = signal_handler_sigint;
// 	sa1.sa_flags = SA_SIGINFO;
// 	sigaction(SIGINT, &sa1, NULL);
// 	sigemptyset(&sa2.sa_mask);
// 	sa2.sa_sigaction = signal_handler_sigquit;
// 	sa2.sa_flags = SA_SIGINFO;
// 	sigaction(SIGQUIT, &sa2, NULL);
// }

void	sigint_handler(int sig)
{
	if (1)
		ft_putstr_fd("\n", STDERR_FILENO);
	// if (1)
	// {
	// 	g_status = 1;
	// 	rl_replace_line("", 0);
	// 	rl_redisplay();
	// 	// rl_done = 1;
	// 	return ;
	// }
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void) sig;
}

void	sigquit_handler(int sig)
{
	ft_putstr_fd("Quit: ", STDERR_FILENO);
	ft_putnbr_fd(sig, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

void	signal_init(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}






// void	sigint_handler(int sig)
// {
// 	if (!g_global.in_heredoc)
// 		ft_putstr_fd("\n", STDERR_FILENO);
// 	if (g_global.in_cmd)
// 	{
// 		g_global.stop_heredoc = 1;
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 		rl_done = 1;
// 		return ;
// 	}
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// 	(void) sig;
// }

// void	sigquit_handler(int sig)
// {
// 	ft_putstr_fd("Quit: ", STDERR_FILENO);
// 	ft_putnbr_fd(sig, STDERR_FILENO);
// 	ft_putchar_fd('\n', STDERR_FILENO);
// }

// void	signal_init(void)
// {
// 	signal(SIGINT, sigint_handler);
// 	signal(SIGQUIT, SIG_IGN);
// }
