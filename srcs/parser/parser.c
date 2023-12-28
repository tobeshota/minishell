/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjia <cjia@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 13:27:33 by toshota           #+#    #+#             */
/*   Updated: 2023/12/28 18:59:06 by cjia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_a_case(t_tools *tools, t_simple_cmds **node,
		t_parser_tools *parser_tools)
{
	if (parser_tools->lexer_list->next == NULL
		&& parser_tools->lexer_list->token != SEMICOLON)
	{
		free(tools->str);
		tools->str = NULL;
		ft_simple_cmdsclear(&tools->simple_cmds);
		ft_lexerclear(&tools->lexer_list);
		implement_tools(tools);
		ft_error(0, tools);
		return (false);
	}
	*node = create_a_node(tools);
	if (!*node)
	{
		parser_error(0, tools);
		return (0);
	}
	if (add_list(&tools->simple_cmds, *node, tools) == false)
		return (0);
	parser_tools->lexer_list = tools->lexer_list;
	return (1);
}

int	handle_b_case(t_tools *tools, t_simple_cmds **node,
		t_parser_tools *parser_tools)
{
	if (handle_operator_error(tools, tools->lexer_list->token))
		return (0);
	*node = creat_ast(parser_tools, tools);
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
		}
		else
		{
			if (!handle_b_case(tools, &node, &parser_tools))
				return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
