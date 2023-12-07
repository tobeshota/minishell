/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjia <cjia@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:11:42 by yoshimurahi       #+#    #+#             */
/*   Updated: 2023/12/06 17:40:40 by cjia             ###   ########.fr       */
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


static int process_str(int index, t_tools *tools) 
{
    int i = index;
    int j = 0;

    i = i + skip(tools->str, i);

    if (check_token(tools->str, i))
        j = handle_token(tools->str, i, &tools->lexer_list);
    else
        j = word_in_node(tools->str, i, &tools->lexer_list);

    if (j < 0)
        return 0;
    i += j;
    
    return i;
}

int lexer(t_tools *tools) 
{
    int i;
    
    i = 0;

    while (tools->str[i]) 
    {
        i = process_str(i, tools);
        if (i == 0)
            return EXIT_FAILURE;  // エラーが発生した場合、または処理が終了した場合にループを抜ける
    }
    return EXIT_SUCCESS;
}

// void	nodefirst_ver_lexer(t_lexer **node)
// {
// 	if (node == NULL || *node == NULL)
// 		return ;
// 	while ((*node)->prev != NULL)
// 		*node = (*node)->prev;
// }

// int main() {
//     t_tools tools;  // lexer 用のデータ構造を作成

//     // tools 構造体を初期化または必要に応じて設定
//     tools.lexer_list = NULL;
    

//     // 入力文字列を設定
//     tools.str = "echo 'Hello, World!' > output.txt";

//     // lexer プログラムを呼び出す
//     lexer(&tools);
//     while(tools.lexer_list && (tools.lexer_list->str || tools.lexer_list->token))
//     {
//         if(tools.lexer_list->str)
//         {
//             printf("%s\n", tools.lexer_list->str);
//         }
//         else if(tools.lexer_list->token)
//             printf("%d\n", tools.lexer_list->token);
        
//         if(tools.lexer_list->next)
//             tools.lexer_list = tools.lexer_list->next;
//         else
//             break;
//     }
//     nodefirst_ver_lexer(&tools.lexer_list);
    
//     free_lexer(tools.lexer_list);
    
//     // t_lexer *tmp = tools.lexer_list;
//     // while(tmp)
//     // {
//     //     if(tmp->str)
//     //          printf("lexer_list->str = %s\n", tmp->str);
//     //     else
//     //         printf("lexer_list->token = %d\n", tmp->token);
//     //     tmp = tmp->next;
//     // }

//     // tools.simple_cmds = NULL;
//     // parser(&tools);

//     // printf("parser_list = %s\n", tools.simple_cmds->str[0]);

//     // while(tools.simple_cmds)
//     // {
//     //    if(tools.simple_cmds->str)
//     //         printf("simple_cmds->str = %s\n", tools.simple_cmds->str[0]);
//     //     else if(tools.simple_cmds->file_name)
//     //         printf("simple_cmds->file_name = %s\n", tools.simple_cmds->file_name);
//     //     else
//     //         printf("simple_cmds->num_redirections = %d\n", tools.simple_cmds->num_redirections);
//     //     tools.simple_cmds = tools.simple_cmds->next;
//     // }

//     // printf("lexer_list = %p\n", tools.lexer_list);
//     return 0;
// }
