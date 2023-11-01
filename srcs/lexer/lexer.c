/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshimurahiro <yoshimurahiro@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:11:42 by yoshimurahi       #+#    #+#             */
/*   Updated: 2023/11/01 09:52:17 by yoshimurahi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"

int skip(char *str, int i)
{
    int j;

    j = 0;
    while(str[j + i] == ' ' || (str[j + i] >= 9 && str[j + i] <= 13))
        j++;
    return (j + i);
}

int process_str(const char *str, int index, t_lexer *lexer_list) 
{
    int i = index;
    int j = 0;

    i += skip(str, i);

    if (handle_token(str, i, lexer_list))
        j = handle_token(str, i, lexer_list);
    else
        j = word_in_node(str, i, lexer_list);

    if (j < 0)
        return 0;

    i += j;

    return i;
}

void lexer(t_tentative *test) 
{
    int i;
    int j;
    
    i = 0;
    j = 0;

    while (test->str[i]) 
    {
        i = process_str(test->str, i, &test->lexer_list);
        if (i == 0)
            return;  // エラーが発生した場合、または処理が終了した場合にループを抜ける
    }
}
