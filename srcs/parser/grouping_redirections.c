/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grouping_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjia <cjia@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:09:54 by yoshimurahi       #+#    #+#             */
/*   Updated: 2023/12/06 15:12:23 by cjia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

static int	add_new_redirection(t_lexer *tmp, t_parser_tools *parser_tools)
{
	t_lexer	*node;
	int		index_1;
	int		index_2;

	if (!tmp->next->str)
	{
		parser_error(4, parser_tools->tools, parser_tools->lexer_list);
		return (1);
	}
	node = make_node(ft_strdup(tmp->next->str), tmp->token);
		//tmpはリダイレクト演算子確定後のノードを指しているので、tmp->next->strはファイル名を指している。
	if (!node)
	{
		parser_error(1, parser_tools->tools, parser_tools->lexer_list);
		return (1);
	}
	add_back_node(&parser_tools->redirections, node);
	index_1 = tmp->i;
	index_2 = tmp->next->i;
	erase_token(&parser_tools->lexer_list, index_1);
	erase_token(&parser_tools->lexer_list, index_2);
	//リダイレクト演算子とファイル名を削除しているindex_1 = tmp->i;はただ、消す場所を指定しているだけ。
	parser_tools->num_redirections++;
	return (0);
}

int	grouping_redirections(t_parser_tools *parser_tools)
{
	t_lexer *tmp;

	tmp = parser_tools->lexer_list;
	while (tmp && tmp->token == 0)
		tmp = tmp->next;
	if (!tmp || tmp->token == PIPE || tmp->token == AND_AND
		|| tmp->token == OR_OR || tmp->token == SEMICOLON)
		return (1);
	//パイプまでリダイレクトがなかったら終了
	if (!tmp->next)
	{
		parser_error(0, parser_tools->tools, parser_tools->lexer_list);
		return (1);
	}
	if (tmp->next->token)
		parser_token_error(parser_tools->tools,
							parser_tools->lexer_list,
							tmp->next->token);
	if ((tmp->token >= GREAT && tmp->token <= OR_OR))
	{
		if (add_new_redirection(tmp, parser_tools) == 1)
			//トークンがリダイレクト演算子である場合、新しいリダイレクション情報が parser_tools 構造体内の redirections リストに追加。
			return (EXIT_FAILURE);
	}
	grouping_redirections(parser_tools); //トークンリスト内のすべてのリダイレクト演算子が処理されるまで続く再帰関数
	return (EXIT_SUCCESS);
}