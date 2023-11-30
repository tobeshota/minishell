/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:34:25 by toshota           #+#    #+#             */
/*   Updated: 2023/11/30 17:20:13 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void init_minishell(char **envp, t_env	**env)
{
	*env = array_to_node(envp);
	get_order(*env);
}

//--------------cjiaの実験場------のちに消す---------------

char	*token_to_char(t_tokens token)
{
	if (token == PIPE)
		return ("|");
	else if (token == GREAT)
		return (">");
	else if (token == GREAT_GREAT)
		return (">>");
	else if (token == LESS)
		return ("<");
	else if (token == LESS_LESS)
		return ("<<");
	else
		return ("");
}

void	nodefirst_ver_simple_cmds(t_simple_cmds **node)
{
	if (node == NULL || *node == NULL)
		return ;
	while ((*node)->prev != NULL)
		*node = (*node)->prev;
}

char **change_to_array(t_tools *tools)
{
	char **tmparray;
	char *tmp2 = NULL;
	int i;
	int j;
	int k;
	t_simple_cmds *tmp;

	i = 0;
	j = 0;
	k = 0;
	tmp = tools->simple_cmds;
	while (tmp)
	{
		if(tmp->str)
			i++;
		if(tmp->redirections)
			i++;
		tmp = tmp->next;
	}
	nodefirst_ver_simple_cmds(&tmp);

	tmparray = check_malloc((char **)malloc(sizeof(char *) * (i + 1)));
	i = 0;
	tmp = tools->simple_cmds;
	while (tmp)
	{
		if(tmp->str[i])
		{
			while(tmp->str[k])
			{
				tmparray[i] = ft_strjoin(tmparray[i], tmp->str[k]);
				if(tmp->str[k + 1])
					tmparray[i] = ft_strjoin(tmparray[i], " ");
				k++;
			}
			i++;
		}
		if(tmp->redirections)
		{
			tmparray[i] = ft_strdup(token_to_char(tmp->redirections->token));
			i++;
			tmparray[i] = ft_strdup(tmp->redirections->str);
			i++;
		}
		tmp = tmp->next;
	}
	tmparray[i] = NULL;
	nodefirst_ver_simple_cmds(&tmp);
	return (tmparray);
}

int	implement_tools(t_tools *tools)
{
	tools->simple_cmds = NULL;
	tools->lexer_list = NULL;
	tools->str = NULL;

	return (1);
}

int	free_tools(t_tools *tools)
{
	ft_simple_cmdsclear(&tools->simple_cmds);
	free(tools->str);
	all_free_tab(tools->envp);
	implement_tools(tools);
	free(tools);
	return (1);
}

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
		put_arg_for_debug(argv);
		if(is_match(line, "putnode"))
			put_node_for_debug(env);
		else
			pipex(argv, &env);
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

	tools = (t_tools *)check_malloc(malloc(sizeof(t_tools)));
	tools->envp = ft_arrdup(envp);

	if(implement_tools(tools) == 0)
	{
		ft_putendl_fd("malloc error", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	while (true)
	{
		line = readline(MINISHELL_PROMPT);
		tools->str = line;
		if (!line)
		{
			free_tools(tools);
			break;
		}
		if (tools->str[0] != '\0')
		{
			// argv = ft_split(line, ',');	/* 本来はft_splitでなくlexerとparser．いまは区切り文字','で分割している */
			lexer(tools);
			parser(tools);
			tmparray = change_to_array(tools);
			tools->simple_cmds->str = expander(tools, tmparray);
			if (*tools->str)
				add_history(tools->str);
			put_arg_for_debug(tmparray);
			if(is_match(tools->str, "putnode"))
				put_node_for_debug(env);
			else
				pipex(tmparray, &env);
			// all_free_tab(tmparray);
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

	// argv[1] = "p";
	if (is_match(argv[1], "p"))
		return (minishell_by_pipex_for_debug(argv, envp));
	if (argc == 1)
		return (minishell(argv, envp, &tools));
	return (put_error("minishell: too many arguments"), 1);
}

//--------------cjiaの実験場------のちに消す---------------


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
