/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjia <cjia@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 13:58:05 by cjia              #+#    #+#             */
/*   Updated: 2023/12/22 09:57:43 by cjia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_in_cmd = 0;

int	minishell(char **envp, t_tools *tools)
{
	t_env	*env;
	char	*line;

	init_minishell(envp, &env);
	tools = (t_tools *)check_malloc(malloc(sizeof(t_tools)));
	while (true)
	{
		signal_init_main();
		line = readline(MINISHELL_PROMPT);
		if (!line)
			break ;
		if (g_in_cmd == SIG_INT_COMING)
			tools->error_num = 1;
		implement_tools(tools);
		tools->str = line;
		if (*tools->str)
			add_history(tools->str);
		handle_input(tools, &env);
	}
	free(tools);
	ft_nodeclear(&env);
	ft_printf(EXIT_MSG);
	return (tools->error_num);
}

int	main(int argc, char **argv, char **envp)
{
	t_tools	tools;

	(void)argv;
	if (argc == 1)
		return (minishell(envp, &tools));
	return (put_error("minishell: too many arguments"), 1);
}

__attribute__((destructor)) static void	destructor()
{
	system("leaks -q minishell");
}
