/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_in_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshimurahiro <yoshimurahiro@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 13:33:42 by yoshimurahi       #+#    #+#             */
/*   Updated: 2023/12/06 09:59:11 by yoshimurahi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"

static int  handle_quotes(int i, char *str, char c) 
{
    int j;
    
    j = 1;
    while (str[i + j] && str[i + j] != c)
        j++;
    j++;
    return j;
}

int word_in_node(char *str, int i, t_lexer **lexer_list) 
{
    int j;
    char *word;
    
    j = 0;
    while (str[i + j] && !get_token_type(str, i + j)) 
    {
        int quotes_len;
        
        quotes_len= 0;

        if (str[i + j] == '\'' || str[i + j] == '"') 
        {
            quotes_len = handle_quotes(i + j, str, str[i + j]);
            j += quotes_len;
        } 
        else if (str[i + j] == ' ' || (str[i + j] >= 9 && str[i + j] <= 13)) 
            break;
        else
            j++;
    }
    word = ft_substr(str, i, j);
    // printf("word = %s\n", word);
    if (!word || !add_node(word, 0, lexer_list))
        return -1;
    return j;
}