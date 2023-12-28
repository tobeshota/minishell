/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjia <cjia@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 11:53:59 by cjia              #+#    #+#             */
/*   Updated: 2023/12/28 19:09:13 by cjia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	add_list(t_simple_cmds **list, t_simple_cmds *new, t_tools *tools)
{
	t_simple_cmds	*tmp;

	tmp = *list;
	if (*list == NULL)
	{
		*list = new;
		return (true);
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	if (check_double_operator(new, tmp, tools) == false)
	{
		return (false);
	}
	return (true);
}

void	grouping_cmd(int arg_size, char **str, t_parser_tools *parser_tools)
{
	t_lexer	*tmp;
	int		i;

	i = 0;
	tmp = parser_tools->lexer_list;
	while (arg_size > 0)
	{
		if (tmp->str)
		{
			str[i++] = ft_strdup(tmp->str);
			erase_token(&parser_tools->lexer_list, tmp->i);
			tmp = parser_tools->lexer_list;
		}
		arg_size--;
	}
}

t_simple_cmds	*creat_ast(t_parser_tools *parser_tools, t_tools *tools)
{
	char	**str;
	int		arg_size;

	str = NULL;
	if (grouping_redirections(parser_tools, tools) == EXIT_FAILURE)
		return (NULL);
	arg_size = count_args(parser_tools->lexer_list);
	str = (char **)check_malloc(ft_calloc(arg_size + 1, sizeof(char *)));
	if (!str)
		parser_error(3, parser_tools->tools);
	grouping_cmd(arg_size, str, parser_tools);
	if (str[0] == NULL && parser_tools->num_redirections == 0)
		return (NULL);
	return (recreated_node(str, parser_tools->num_redirections,
			parser_tools->redirections));
}

t_parser_tools	init_parser_tools(t_tools *tools)
{
	t_parser_tools	parser_tools;

	parser_tools.lexer_list = tools->lexer_list;
	parser_tools.redirections = NULL;
	parser_tools.num_redirections = 0;
	parser_tools.tools = tools;
	return (parser_tools);
}

t_simple_cmds	*create_a_node(t_tools *tools)
{
	t_simple_cmds	*node;

	node = (t_simple_cmds *)malloc(sizeof(t_simple_cmds));
	if (!node)
		return (NULL);
	node->redirections = (t_lexer *)malloc(sizeof(t_lexer));
	if (!node->redirections)
	{
		free(node);
		return (NULL);
	}
	node->redirections->str = NULL;
	node->redirections->token = tools->lexer_list->token;
	node->redirections->next = NULL;
	node->redirections->prev = NULL;
	node->str = NULL;
	node->num_redirections = 0;
	node->next = NULL;
	node->prev = NULL;
	erase_token(&tools->lexer_list, tools->lexer_list->i);
	return (node);
}
