/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjia <cjia@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:09:49 by yoshimurahi       #+#    #+#             */
/*   Updated: 2023/12/08 10:28:44 by cjia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include "pipex.h"

t_simple_cmds	*recreated_node(char **str,
								int num_redirections,
								t_lexer *redirections)
{
	t_simple_cmds	*new_element;

	new_element = (t_simple_cmds *)check_malloc(malloc(sizeof(t_simple_cmds)));
	// printf("str = %p\n", *str);
	if (!new_element)
		return (0);
	new_element->str = str;
	new_element->num_redirections = num_redirections;
	new_element->redirections = redirections;
	new_element->next = NULL;
	new_element->prev = NULL;
	return (new_element);
}

int	count_args(t_lexer *lexer_list)
{
	t_lexer	*tmp;
	int		i;

	i = 0;
	if (!lexer_list)
		return (0);
	tmp = lexer_list;
	while (tmp && tmp->token != PIPE && tmp->token != AND_AND
		&& tmp->token != OR_OR && tmp->token != SEMICOLON)
	{
		if (tmp->i >= 0)
			i++;
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	return (i);
}

static t_lexer	*ft_lexerclear_one(t_lexer **lst)
{
	if ((*lst)->str)
	{
		free((*lst)->str);
		(*lst)->str = NULL;
	}
	free(*lst);
	*lst = NULL;
	return (NULL);
}

static void	ft_lexerdel_first(t_lexer **lst)
{
	t_lexer	*node;

	node = *lst;
	*lst = node->next;
	ft_lexerclear_one(&node);
	if (*lst)
		(*lst)->prev = NULL;
}

void	erase_token(t_lexer **lexer_list, int i)
{
	t_lexer *node;
	t_lexer *prev;
	t_lexer *start;

	start = *lexer_list;
	node = start;
	if ((*lexer_list)->i == i)
	{
		ft_lexerdel_first(lexer_list);
		return ;
	}
	while (node && node->i != i)
	{
		prev = node;
		node = node->next;
	}
	if (node)
		prev->next = node->next;
	else
		prev->next = NULL;
	if (prev->next)
		prev->next->prev = prev;
	ft_lexerclear_one(&node);
	*lexer_list = start;
}