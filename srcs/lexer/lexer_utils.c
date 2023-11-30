/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshimurahiro <yoshimurahiro@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 13:10:27 by yoshimurahi       #+#    #+#             */
/*   Updated: 2023/11/30 15:22:51 by yoshimurahi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"

int     get_token_type(char *str, int i) {
    int token_type = NONE;

    if (str[i] == '|') 
        token_type = PIPE;
    else if (str[i] == '>') 
    {
        if (str[i + 1] == '>')
            token_type = GREAT_GREAT;
        else
            token_type = GREAT;
    } 
    else if (str[i] == '<') 
    {
        if (str[i + 1] == '<')
            token_type = LESS_LESS;
        else
            token_type = LESS;
    }
    return token_type;
}

t_lexer	*make_node(char *str, int token)
{
	t_lexer		*new_node;
	static int	i = 0;

	new_node = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new_node)
		return (0);
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
    // printf("node = %p\n", node);
    // printf("node->str = %s\n", node->str);
	add_back_node(lexer_list, node);
    // printf("lexer_list = %s\n", node->str);
	return (1);
}