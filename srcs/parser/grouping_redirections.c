/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grouping_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjia <cjia@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:09:54 by yoshimurahi       #+#    #+#             */
/*   Updated: 2023/12/08 13:12:04 by cjia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_new_redirection(t_lexer *tmp, t_parser_tools *parser_tools)
{
	t_lexer	*node;
	int		index_1;
	int		index_2;

	if (!tmp->next->str)
	{
		parser_error(4, parser_tools->lexer_list);
		return (1);
	}
	node = make_node(ft_strdup(tmp->next->str), tmp->token);
	if (!node)
	{
		parser_error(1, parser_tools->lexer_list);
		return (1);
	}
	add_back_node(&parser_tools->redirections, node);
	index_1 = tmp->i;
	index_2 = tmp->next->i;
	erase_token(&parser_tools->lexer_list, index_1);
	erase_token(&parser_tools->lexer_list, index_2);
	parser_tools->num_redirections++;
	return (0);
}

int	grouping_redirections(t_parser_tools *parser_tools)
{
	t_lexer	*tmp;

	tmp = parser_tools->lexer_list;
	while (tmp && tmp->token == 0)
		tmp = tmp->next;
	if (!tmp || tmp->token == PIPE || tmp->token == AND_AND
		|| tmp->token == OR_OR || tmp->token == SEMICOLON)
		return (EXIT_SUCCESS);
	if (!tmp->next)
	{
		parser_error(0, parser_tools->lexer_list);
		parser_tools->lexer_list->token = 0;
		parser_tools->lexer_list = NULL;
		return (1);
	}
	if (tmp->next->token)
		return (parser_token_error(parser_tools->tools,
									parser_tools->lexer_list,
									tmp->next->token),
				EXIT_FAILURE);
	if ((tmp->token >= GREAT && tmp->token <= OR_OR))
	{
		if (add_new_redirection(tmp, parser_tools) == 1)
			return (EXIT_FAILURE);
	}
	grouping_redirections(parser_tools);
	return (EXIT_SUCCESS);
}
