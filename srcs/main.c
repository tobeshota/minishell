#include "minishell.h"

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

void put_node_for_debug(t_env *node)
{
	while(node->next)
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

	if (getenv("SHLVL") == NULL)
		return ;
	shlvl_nb = ft_atoi(getenv("SHLVL"));
	shlvl_str = check_malloc(ft_itoa(shlvl_nb + 1));
	update_envp(env, "SHLVL=", shlvl_str);
	free(shlvl_str);
}

void	init_minishell(char **envp, t_env **env)
{
	*env = array_to_node(envp);
	add_shlvl(env);
	get_order(*env);
}


# define MINIPIPEX_PROMPT "\x1b[32mminipipex $ \x1b[0m\x1b[39m"
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
		argv = ft_split(line, ',');	/* 本来はft_splitでなくlexerとparser．いまは区切り文字','で分割している */
		if (*line)
			add_history(line);
		if(is_match(line, "putnode"))
			put_node_for_debug(env);
		else
			loop_pipex(argv, envp, &env);
		all_free_tab(argv);
		free(line);
	}
	ft_nodeclear(&env);
	ft_printf(EXIT_MSG);
	return (0);
}

int process_input(t_tools *tools, t_env **env) {
    if (lexer(tools) == EXIT_FAILURE)
        return ft_error(1, tools);

    if (tools->lexer_list->token == PIPE || tools->lexer_list->token == AND_AND || tools->lexer_list->token == OR_OR) {// || tools->lexer_list->token == SEMICOLON
        if (parser_token_error(tools, tools->lexer_list, tools->lexer_list->token) == EXIT_FAILURE)
            return 0;
    }

    if (parser(tools) == EXIT_FAILURE) {
        free_tools(tools);
        return 0;
    }

    return 1;
}

int handle_input(t_tools *tools, char **envp, t_env **env) {
    char *line;
    char **tmparray;

    line = readline(MINISHELL_PROMPT);
    implement_tools(tools);
    tools->str = line;
    if (!line) {
        free_tools(tools);
        return 0;
    }
    if (tools->str[0] != '\0') {
        if (!process_input(tools, env))
            return 0;
		signal(SIGQUIT, sigquit_handler);
        tmparray = change_to_array(tools);
        tools->simple_cmds->str = expander(tools, tmparray);
        if (*tools->str)
            add_history(tools->str);
        put_arg_for_debug(tmparray);
        if (is_match(tools->str, "putnode"))
            put_node_for_debug(*env);
        else
            g_global.error_num = loop_pipex(tmparray, envp, env);
        node_to_array(*env, &tools->envp);
        free_tools(tools);
    }
    return 1;
}


int minishell(char **argv, char **envp, t_tools *tools) {
    t_env *env;

    init_minishell(envp, &env);
    while (true) {
        tools = (t_tools *)check_malloc(malloc(sizeof(t_tools)));
        if (implement_tools(tools) == 0)
            exit(EXIT_FAILURE);
        tools->envp = ft_arrdup(envp);
		handle_input(tools, envp, &env);
    }
    ft_nodeclear(&env);
    ft_printf(EXIT_MSG);
    return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_tools	tools;

	if (argc == 2 && is_match(argv[1], "p"))
		return (minipipex(argv, envp));
	if (argc == 1)
		return (minishell(argv, envp, &tools));
	return (put_error("minishell: too many arguments"), 1);
}


__attribute__((destructor)) static void destructor()
{
	system("leaks -q minishell");
}
