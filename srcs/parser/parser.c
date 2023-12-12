/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjia <cjia@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 13:27:33 by toshota           #+#    #+#             */
/*   Updated: 2023/12/12 15:31:54 by cjia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// bool check_double_operator(t_simple_cmds *new, t_simple_cmds *tmp, t_tools *tools)
// {
// 	if (tmp->redirections && (tmp->redirections->token == SEMICOLON
// 		|| tmp->redirections->token == AND_AND
// 		|| tmp->redirections->token == OR_OR
// 		|| tmp->redirections->token == PIPE))
// 	{
// 		if (tmp->redirections && (new->redirections->token == SEMICOLON
// 			|| new->redirections->token == AND_AND
// 			|| new->redirections->token == OR_OR
// 			|| new->redirections->token == PIPE))
// 		{
// 			parser_error(0, tools);
// 			return false;
// 		}
// 	}
// 	return true;
// }

bool	add_list(t_simple_cmds **list, t_simple_cmds *new, t_tools *tools)
{
	t_simple_cmds	*tmp;

	tmp = *list;
	if (*list == NULL)
	{
		*list = new;
		return true;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	// if(check_double_operator(new, tmp, tools) == false)
	// 	return false;
	return true;
}

static t_simple_cmds	*creat_ast(t_parser_tools *parser_tools)
{
	char	**str;
	int		i;
	int		arg_size;
	t_lexer	*tmp;

	i = 0;
	str = NULL;
	if (grouping_redirections(parser_tools) == EXIT_FAILURE)
		return (NULL);
	arg_size = count_args(parser_tools->lexer_list);
	str = (char **)check_malloc(ft_calloc(arg_size + 1, sizeof(char *)));
	if (!str)
		parser_error(1, parser_tools->tools);
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
	if (str[0] == NULL && parser_tools->num_redirections == 0)
		return (NULL);
	return (recreated_node(str, parser_tools->num_redirections,
			parser_tools->redirections));
}

static t_parser_tools	init_parser_tools(t_tools *tools)
{
	t_parser_tools	parser_tools;

	parser_tools.lexer_list = tools->lexer_list;
	parser_tools.redirections = NULL;
	parser_tools.num_redirections = 0;
	parser_tools.tools = tools;
	return (parser_tools);
}

static t_simple_cmds	*create_a_node(t_tools *tools)
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

int	handle_a_case(t_tools *tools, t_simple_cmds **node,
		t_parser_tools *parser_tools)
{
	if (parser_tools->lexer_list->next == NULL
		&& parser_tools->lexer_list->token != SEMICOLON)
	{
		parser_error(0, tools);
		// ft_lexerclear(&parser_tools->lexer_list);
		// ft_lexerclear(&parser_tools->redirections);
		// ft_error(0);
		return (0);
	}
	*node = create_a_node(tools);
	if (!*node)
	{
		parser_error(0, tools);
		return (0);
	}
	if(add_list(&tools->simple_cmds, *node, tools) == false)
		return (0);
	parser_tools->lexer_list = tools->lexer_list;
	return (1);
}

int	handle_b_case(t_tools *tools, t_simple_cmds **node,
		t_parser_tools *parser_tools)
{
	if (handle_operator_error(tools, tools->lexer_list->token))
		return (0);
	*node = creat_ast(parser_tools);
	if (!*node)
	{
		return (0);
	}
	add_list(&tools->simple_cmds, *node, tools);
	tools->lexer_list = parser_tools->lexer_list;
	return (1);
}

int	parser(t_tools *tools)
{
	t_simple_cmds	*node;
	t_parser_tools	parser_tools;

	node = NULL;
	while (tools->lexer_list)
	{
		parser_tools = init_parser_tools(tools);
		if ((tools->lexer_list && tools->lexer_list->token == PIPE)
			|| tools->lexer_list->token == AND_AND
			|| tools->lexer_list->token == OR_OR
			|| tools->lexer_list->token == SEMICOLON)
		{
			if (!handle_a_case(tools, &node, &parser_tools))
				return (EXIT_FAILURE);
			// if(tools->simple_cmds->prev && (tools->simple_cmds->prev->redirections->token == SEMICOLON
			// 	|| tools->simple_cmds->prev->redirections->token == AND_AND
			// 	|| tools->simple_cmds->prev->redirections->token == OR_OR
			// 	|| tools->simple_cmds->prev->redirections->token == PIPE))//探索できるようにする。これでは最初に照準を合わせているだけ
			// {
			// 	parser_error(0, tools);
			// 	return (0);
			// }
		}
		else
		{
			if (!handle_b_case(tools, &node, &parser_tools))
				return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
