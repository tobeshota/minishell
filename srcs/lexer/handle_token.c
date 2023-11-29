/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshimurahiro <yoshimurahiro@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:12:33 by yoshimurahi       #+#    #+#             */
/*   Updated: 2023/11/22 13:15:29 by yoshimurahi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"

int handle_token(char *str, int i, t_lexer **lexer_list) {
    int token_type = get_token_type(str, i);
    
    if (token_type == NONE) 
        return 0;

    if (token_type == GREAT_GREAT || token_type == LESS_LESS) 
    {
        // printf("token_type = %d\n", token_type);
        if (!add_node(NULL, token_type, lexer_list))
            return -1;
        return 2;
    }
    else
    {
        // printf("token_type = %d\n", token_type);
        if (!add_node(NULL, token_type, lexer_list))
            return -1;
        return 1;
    }
}

int check_token(char *str, int i, t_lexer **lexer_list) {
    int token_type = get_token_type(str, i);
    
    if (token_type == NONE) 
        return 0;

    if (token_type == GREAT_GREAT || token_type == LESS_LESS) 
    {
        return 2;
    }
    else
    {
        return 1;
    }
}