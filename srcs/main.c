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

//--------------cjiaの実験場------のちに消す---------------

# define MINIPIPEX_PROMPT "\x1b[32mminipipex $ \x1b[0m\x1b[39m"
/* lexer(); と parser(); のない minishell ． pipex のテスト用 */
int	minishell_by_pipex_for_debug(char **argv, char **envp)
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
		// put_arg_for_debug(argv);
		if(is_match(line, "putnode"))
			put_node_for_debug(env);
		else
			loop_pipex(argv, &env);
		all_free_tab(argv);
		node_to_array(env, &envp);
		free(line);
	}
	ft_nodeclear(&env);
	ft_printf(EXIT_MSG);
	return (0);
}

int	minishell(char **argv, char **envp, t_tools *tools)
{
	char	*line;
	t_env	*env;
	char	**tmparray;

	init_minishell(envp, &env);
	while (true)
	{
		tools = (t_tools *)check_malloc(malloc(sizeof(t_tools)));
		if(implement_tools(tools) == 0)
			exit(EXIT_FAILURE);
		tools->envp = ft_arrdup(envp);
		line = readline(MINISHELL_PROMPT);
		implement_tools(tools);
		tools->str = line;
		if (!line)
		{
			free_tools(tools);
			break;
		}
		if (tools->str[0] != '\0')
		{
			if(lexer(tools) == EXIT_FAILURE)
				return (ft_error(1, tools));
			if (tools->lexer_list->token == PIPE)
			{
				if(parser_double_token_error(tools, tools->lexer_list,
						tools->lexer_list->token) == EXIT_FAILURE)
					continue ;
			}
			if(parser(tools) == EXIT_FAILURE)
				return (ft_error(3, tools));
			tmparray = change_to_array(tools);
			tools->simple_cmds->str = expander(tools, tmparray);//修正点：ここで”echo $?”が"0"のみになった
			if (*tools->str)
				add_history(tools->str);
			put_arg_for_debug(tmparray);
			if(is_match(tools->str, "putnode"))
				put_node_for_debug(env);
			else
				g_global.error_num = loop_pipex(tmparray, &env);
			node_to_array(env, &envp);
			free_tools(tools);
		}
	}
	ft_nodeclear(&env);
	ft_printf(EXIT_MSG);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_tools	tools;

	// if (argc == 2 && is_match(argv[1], "p"))
		return (minishell_by_pipex_for_debug(argv, envp));
	if (argc == 1)
		return (minishell(argv, envp, &tools));
	return (put_error("minishell: too many arguments"), 1);
}

// --------------cjiaの実験場------のちに消す---------------


// int	minishell(char **argv, char **envp)
// {
// 	char	*line;
// 	t_env	*env;

// 	init_minishell(envp, &env);
// 	while (true)
// 	{
// 		line = readline(MINISHELL_PROMPT);
// 		if (!line)
// 			break ;
// 		argv = ft_split(line, ',');	/* 本来はft_splitでなくlexerとparser．いまは区切り文字','で分割している */

// 		if (*line)
// 			add_history(line);
// 		put_arg_for_debug(argv);
// 		if(is_match(line, "putnode"))
// 			put_node_for_debug(env);
// 		else
// 			pipex(argv, &env);
// 		all_free_tab(argv);
// 		node_to_array(env, &envp);
// 		free(line);
// 	}
// 	ft_nodeclear(&env);
// 	ft_printf(EXIT_MSG);
// 	return (0);
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	t_tools	tools;
// 	if (argc == 1 || argc != 1)
// 		minishell(argv, envp);
// }

__attribute__((destructor)) static void destructor()
{
	system("leaks -q minishell");
}
