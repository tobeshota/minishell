/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjia <cjia@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 13:46:33 by toshota           #+#    #+#             */
/*   Updated: 2023/12/19 14:02:32 by cjia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_shlvl(t_env **env)
{
	int		shlvl_nb;
	char	*shlvl_str;

	if (getenv_from_t_env(*env, "SHLVL=") == NULL)
		return ;
	shlvl_nb = ft_atoi(getenv_from_t_env(*env, "SHLVL=") + ft_strlen("SHLVL="));
	shlvl_str = check_malloc(ft_itoa(shlvl_nb + 1));
	update_envp(env, "SHLVL=", shlvl_str);
	free(shlvl_str);
}

static void	add_basic_shell_variables(t_env **env)
{
	char	cwd[PATH_MAX];
	char	*cwd_w_varname;

	if (getcwd(cwd, PATH_MAX) == NULL)
		return ;
	cwd_w_varname = check_malloc(ft_strjoin("PWD=", cwd));
	*env = ft_nodenew(cwd_w_varname);
	ft_nodeadd_back(env, ft_nodenew("SHLVL=0"));
	ft_nodeadd_back(env, ft_nodenew("_=./minishell"));
	free(cwd_w_varname);
}

static int	process_input(t_tools *tools)
{
	if (lexer(tools) == EXIT_FAILURE)
		return (ft_error(1, tools));
	if (tools->lexer_list->token == PIPE
		|| tools->lexer_list->token == SEMICOLON
		|| tools->lexer_list->token == AND_AND
		|| tools->lexer_list->token == OR_OR)
	{
		if (parser_token_error(tools, tools->lexer_list->token) == EXIT_FAILURE)
			return (0);
	}
	if (tools->lexer_list->token == 0 && tools->lexer_list->str[0] == '\0')
	{
		ft_lexerclear(&tools->lexer_list);
		return (0);
	}
	if (parser(tools) == EXIT_FAILURE)
	{
		return (0);
	}
	return (1);
}

int	handle_input(t_tools *tools, t_env **env)
{
	char	**h_envp;

	if (tools->str[0] != '\0')
	{
		if (!count_quotes(tools->str))
			return (free(tools->str), ft_error(2, tools));
		if (!process_input(tools))
			return (false);
		signal(SIGQUIT, sigquit_handler);
		tools->tmp_array = change_to_array(tools);
		h_envp = node_to_array(*env);
		tools->simple_cmds->str = expander(tools, tools->tmp_array, h_envp);
		all_free_tab(h_envp);
		g_in_cmd = IN_CMD;
		tools->error_num = loop_pipex(tools, env);
		free_tools(tools);
		g_in_cmd = 0;
		return (true);
	}
	free_tools(tools);
	return (false);
}

void	init_minishell(char **envp, t_env **env)
{
	if (envp[0] == NULL)
		add_basic_shell_variables(env);
	else
		*env = array_to_node(envp);
	add_shlvl(env);
	get_order(*env);
}
