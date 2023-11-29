/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshimurahiro <yoshimurahiro@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:11:42 by yoshimurahi       #+#    #+#             */
/*   Updated: 2023/11/29 12:40:20 by yoshimurahi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"

static int skip(char *str, int i)
{
    int j;

    j = 0;
    while(str[j + i] == ' ' || (str[j + i] >= 9 && str[j + i] <= 13))
        j++;
    return (j);
}


static int process_str(int index, t_tools *lexer_tools) 
{
    int i = index;
    int j = 0;


    i = i + skip(lexer_tools->str, i);

    if (check_token(lexer_tools->str, i, &lexer_tools->lexer_list))
        j = handle_token(lexer_tools->str, i, &lexer_tools->lexer_list);
    else
        j = word_in_node(lexer_tools->str, i, &lexer_tools->lexer_list);

    if (j < 0)
        return 0;
    i += j;
    
    return i;
}

void lexer(t_tools *lexer_tools) 
{
    int i;
    
    i = 0;

    while (lexer_tools->str[i]) 
    {
        i = process_str(i, lexer_tools);
        if (i == 0)
            return;  // エラーが発生した場合、または処理が終了した場合にループを抜ける
    }
}


// int main() {
//     t_tools lexer_tools;  // lexer 用のデータ構造を作成

//     // lexer_tools 構造体を初期化または必要に応じて設定
//     lexer_tools.lexer_list = NULL;
    

//     // 入力文字列を設定
//     lexer_tools.str = "echo 'Hello, World!' > output.txt";

//     // lexer プログラムを呼び出す
//     lexer(&lexer_tools);
    
//     // t_lexer *tmp = lexer_tools.lexer_list;
//     // while(tmp)
//     // {
//     //     if(tmp->str)
//     //          printf("lexer_list->str = %s\n", tmp->str);
//     //     else
//     //         printf("lexer_list->token = %d\n", tmp->token);
//     //     tmp = tmp->next;
//     // }

//     lexer_tools.simple_cmds = NULL;
//     parser(&lexer_tools);

//     printf("parser_list = %s\n", lexer_tools.simple_cmds->str[0]);

//     while(lexer_tools.simple_cmds)
//     {
//        if(lexer_tools.simple_cmds->str)
//             printf("simple_cmds->str = %s\n", lexer_tools.simple_cmds->str[0]);
//         else if(lexer_tools.simple_cmds->file_name)
//             printf("simple_cmds->file_name = %s\n", lexer_tools.simple_cmds->file_name);
//         else
//             printf("simple_cmds->num_redirections = %d\n", lexer_tools.simple_cmds->num_redirections);
//         lexer_tools.simple_cmds = lexer_tools.simple_cmds->next;
//     }

//     // printf("lexer_list = %p\n", lexer_tools.lexer_list);
//     return 0;
// }





// static int process_str(char *str, int index, t_lexer *lexer_list, t_tools *lexer_tools) 
// {
//     int i = index;
//     int j = 0;


//     i = i + skip(str, i);

//     if (handle_token(str, i, &lexer_list))
//         j = handle_token(str, i, &lexer_list);
//     else
//         j = word_in_node(str, i, &lexer_list);

//     if (j < 0)
//         return 0;
//     i += j;
//     printf("lexer_list->str1 = %s\n", lexer_list->str);
//     printf("lexer_list->str2 = %s\n", lexer_tools->lexer_list->str);
//     return i;
// }

// void lexer(t_tools *lexer_tools) 
// {
//     int i;
    
//     i = 0;

//     while (lexer_tools->str[i]) 
//     {
//         i = process_str(lexer_tools->str, i, lexer_tools->lexer_list, lexer_tools);
//         if (i == 0)
//             return;  // エラーが発生した場合、または処理が終了した場合にループを抜ける
//         // printf("lexer_list = %s\n", lexer_tools->lexer_list->str);
//     }
// }