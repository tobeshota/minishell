/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshimurahiro <yoshimurahiro@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 13:37:16 by yoshimurahi       #+#    #+#             */
/*   Updated: 2023/11/22 11:28:51 by yoshimurahi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include "../libft/inc/libft.h"
# include "../inc/parser.h"
# include "minishell.h"


// typedef enum s_tokens
// {
// 	PIPE = 1,
// 	GREAT,
// 	GREAT_GREAT,
// 	LESS,
// 	LESS_LESS,
// 	NONE = 0,
// }	t_tokens;


// typedef struct s_lexer
// {
//     struct s_lexer	*next;
// 	struct s_lexer	*prev;
//     char			*str;
// 	int				i;
// 	t_tokens 		token;
// }   t_lexer;

// typedef struct s_tools
// {
//     char                    *str;
// 	struct s_simple_cmds	*simple_cmds;
//     t_lexer					*lexer_list;
// 	char 					**envp;
// }   t_tools;


// void lexer(t_tools *lexer_tools);
// int handle_token(char *str, int i, t_lexer **lexer_list);
// int word_in_node(char *str, int i, t_lexer **lexer_list);
// int get_token_type(char *str, int i);
// int add_node(char *str,  t_tokens token, t_lexer **lexer_list);
// char	*ft_substr(const char *s, unsigned int start, size_t len);
// size_t	ft_strlen(const char *str);
// char	*ft_strdup(const char *src);




// void print_lexer(t_lexer *lexer_list);
// void print_parser(t_simple_cmds simple_cmds);
// t_parser_tools	init_parser_tools(t_lexer *lexer_list, t_tools *tools);


#endif