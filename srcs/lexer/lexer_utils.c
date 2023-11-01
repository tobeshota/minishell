/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshimurahiro <yoshimurahiro@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 13:10:27 by yoshimurahi       #+#    #+#             */
/*   Updated: 2023/11/01 09:53:03 by yoshimurahi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"

int get_token_type(char *str, int i) {
    int token_type = NONE;

    if (str[i] == '|') 
        token_type = PIPE;
    else if (str[i] == '>' && str[i + 1] == '>') 
        token_type = GREAT_GREAT;
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

int add_node(char *str, int token_type, t_lexer **lexer_list) 
{
    t_lexer *new_node;
    t_lexer *tmp;

    new_node = malloc(sizeof(t_lexer));
    if (!new_node)
        return 0;
    new_node->str = str;
    new_node->token_head.str = NULL;
    new_node->token_head.type = token_type;
    new_node->token_head.next = NULL;
    new_node->next = NULL;
    new_node->prev = NULL;
    if (!*lexer_list)
        *lexer_list = new_node;
    else 
    {
        tmp = *lexer_list;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new_node;
        new_node->prev = tmp;
    }
    return 1;
}
