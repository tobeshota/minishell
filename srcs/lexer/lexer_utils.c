/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjia <cjia@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 13:10:27 by yoshimurahi       #+#    #+#             */
/*   Updated: 2023/12/08 13:11:41 by cjia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_token_type(char *str, int i)
{
	int	token_type;

	token_type = NONE;
	if (str[i] == '>' && str[i + 1] == '>')
		token_type = GREAT_GREAT;
	else if (str[i] == '>')
		token_type = GREAT;
	else if (str[i] == '<' && str[i + 1] == '<')
		token_type = LESS_LESS;
	else if (str[i] == '<')
		token_type = LESS;
	else if (str[i] == ';')
		token_type = SEMICOLON;
	else if (str[i] == '&' && str[i + 1] == '&')
		token_type = AND_AND;
	else if (str[i] == '|' && str[i + 1] == '|')
		token_type = OR_OR;
	else if (str[i] == '|')
		token_type = PIPE;
	return (token_type);
}

t_lexer	*make_node(char *str, int token)
{
	t_lexer		*new_node;
	static int	i;

	i = 0;
	new_node = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new_node)
		return (NULL);
	new_node->str = str;
	new_node->token = token;
	new_node->i = i++;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

void	add_back_node(t_lexer **lexer_list, t_lexer *node)
{
	t_lexer	*tmp;

	tmp = *lexer_list;
	if (*lexer_list == NULL)
	{
		*lexer_list = node;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = node;
	node->prev = tmp;
}

int	add_node(char *word, t_tokens token, t_lexer **lexer_list)
{
	t_lexer	*node;

	node = make_node(word, token);
	if (!node)
		return (0);
	add_back_node(lexer_list, node);
	return (1);
}
