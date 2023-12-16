#include "minishell.h"

int in_cmd = 0;

static void	put_arg_for_debug(char **argv)
{
	int	i;

	i = -1;
	if (argv[0] != NULL)
		ft_printf("splitted: ");
	while (argv[++i])
		ft_printf("\"%s\"\t", argv[i]);
	if (argv[0] != NULL)
		ft_printf("\n");
}

void	put_array_for_debug(char **str)
{
	while (*str)
	{
		ft_printf(">>>\t[%s]\n", *str);
		str++;
	}
}

void	put_node_for_debug(t_env *node)
{
	while (node->next)
	{
		ft_printf("%5d\t%s\n", node->order, node->content);
		ft_nodenext(&node);
	}
	ft_printf("%5d\t%s\n", node->order, node->content);
	ft_nodefirst(&node);
}

void	add_shlvl(t_env **env)
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

void	add_basic_shell_variables(t_env **env)
{
	char	cwd[PATH_MAX];
	char	*cwd_w_varname;

	if (getcwd(cwd, PATH_MAX) == NULL)
		return ;
	cwd_w_varname = check_malloc(ft_strjoin("PWD=", cwd));
	*env = ft_nodenew(cwd_w_varname);
	ft_nodeadd_back(env, ft_nodenew("SHLVL=0"));
	ft_nodeadd_back(env, ft_nodenew("_=./minishell"));
	// envp[0] = check_malloc(ft_strdup(cwd_w_varname));
	// envp[1] = check_malloc(ft_strdup("SHLVL=0"));
	// envp[2] = check_malloc(ft_strdup("_=./minishell"));
	// envp[3] = NULL;
	free(cwd_w_varname);
}

void	init_minishell(char **envp, t_env **env)
{
	// envp[0] = NULL;
	if (envp[0] == NULL)
		add_basic_shell_variables(env);
	else
		*env = array_to_node(envp);
	add_shlvl(env);
	get_order(*env);
}

#define MINIPIPEX_PROMPT "\x1b[32mminipipex $ \x1b[0m\x1b[39m"

/* lexer(); と parser(); のない minishell ． pipex のテスト用 */
int	minipipex(char **argv, char **envp)
{
	char	*line;
	t_env	*env;

	init_minishell(envp, &env);
	while (true)
	{
		line = readline(MINIPIPEX_PROMPT);
		if (!line)
			break ;
		argv = ft_split(line, ',');
		/* 本来はft_splitでなくlexerとparser．いまは区切り文字','で分割している */
		if (*line)
			add_history(line);
		put_arg_for_debug(argv);
		if (is_match(line, "putnode"))
			put_node_for_debug(env);
		else
			loop_pipex(argv, &env);
		all_free_tab(argv);
		free(line);
	}
	ft_nodeclear(&env);
	ft_printf(EXIT_MSG);
	return (0);
}
// /*
int	process_input(t_tools *tools)
{
	if (lexer(tools) == EXIT_FAILURE)
		return (ft_error(1));
	if (tools->lexer_list->token == PIPE
		|| tools->lexer_list->token == SEMICOLON
		|| tools->lexer_list->token == AND_AND
		|| tools->lexer_list->token == OR_OR)
	{
		if (parser_token_error(tools, tools->lexer_list,
				tools->lexer_list->token) == EXIT_FAILURE)
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

void	ft_nodefirst_cmdsver(t_simple_cmds **node)
{
	if (node == NULL || *node == NULL)
		return ;
	while ((*node)->prev != NULL)
		*node = (*node)->prev;
}

void	check_exit(t_tools *tools, char **argv, t_env **env)
{
	t_simple_cmds	*node;

	node = tools->simple_cmds;
	while (node && node->str)
	{
		if (is_match(node->str[0], "exit") == true)
		{
			free_tools(tools);
			argv = check_malloc(ft_split("exit", ':'));
			g_global.error_num = loop_pipex(argv, env);
		}
		node = node->next;
	}
}

int	handle_input(t_tools *tools, t_env **env, char **argv)
{
	char	**h_envp;

	if (tools->str[0] != '\0')
	{
		if (!count_quotes(tools->str))
			return (free(tools->str), ft_error(2));
		if (!process_input(tools))
			return (false);
		signal(SIGQUIT, sigquit_handler);
		tools->tmp_array = change_to_array(tools);
		h_envp = node_to_array(*env);
		tools->simple_cmds->str = expander(tools, tools->tmp_array, h_envp);
		all_free_tab(h_envp);
		put_arg_for_debug(tools->tmp_array);
		in_cmd = 1;
		check_exit(tools, argv, env);
		g_global.error_num = loop_pipex(tools->tmp_array, env);
		free_tools(tools);
		in_cmd = 0;
		return (true);
	}
	free_tools(tools);
	return (false);
}

int	minishell(char **envp, t_tools *tools, char **argv)
{
	t_env	*env;
	char	*line;

	init_minishell(envp, &env);
	tools = (t_tools *)check_malloc(malloc(sizeof(t_tools)));
	while (true)
	{
		signal_init_main(tools);
		line = readline(MINISHELL_PROMPT);
		if (!line)
			break ;
		implement_tools(tools);
		tools->str = line;
		if (*tools->str)
			add_history(tools->str);
		handle_input(tools, &env, argv);
	}
	free(tools);
	ft_nodeclear(&env);
	ft_printf(EXIT_MSG);
	return (0);
}
// */
int	main(int argc, char **argv, char **envp)
{
	t_tools	tools;

	if (argc == 2 && is_match(argv[1], "p"))
		return (minipipex(argv, envp));
	if (argc == 1)
		return (minishell(envp, &tools, argv));
	return (put_error("minishell: too many arguments"), 1);
}

// __attribute__((destructor)) static void destructor()
// {
// 	system("leaks -q minishell");
// }
