/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 12:55:55 by cjia              #+#    #+#             */
/*   Updated: 2023/12/28 17:31:18 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "define.h"
# define EXIT_FAILURE 1
# define EXIT_SUCCESS 0

// about lexer
int							lexer(t_tools *lexer_tools);
int							handle_token(char *str, int i,
								t_lexer **lexer_list);
int							word_in_node(char *str, int i,
								t_lexer **lexer_list);
int							get_token_type(char *str, int i);
int							add_node(char *str, t_tokens token,
								t_lexer **lexer_list);
void						print_lexer(t_lexer *lexer_list);
void						add_back_node(t_lexer **lexer_list, t_lexer *node);
t_lexer						*make_node(char *str, int token);
int							check_token(char *str, int i);
void						free_lexer(t_lexer *lexer);

// about parser
int							parser(t_tools *tools);
void						erase_token(t_lexer **lexer_list, int i);
int							count_args(t_lexer *lexer_list);
t_simple_cmds				*recreated_node(char **str, int num_redirections,
								t_lexer *redirections);
int							grouping_redirections(t_parser_tools *parser_tools);
void						parser_error(int error, t_tools *tools);
int							parser_token_error(t_tools *tools, t_tokens token);
int							handle_operator_error(t_tools *tools,
								t_tokens token);

char						**change_to_array(t_tools *tools);
int							process_redirections(char **tmparray,
								t_simple_cmds *tmp, int i);
int							process_redirection_str(char **tmparray,
								t_simple_cmds *tmp, int i);

int							ft_error(int error, t_tools *tools);

bool						check_double_operator(t_simple_cmds *new,
								t_simple_cmds *tmp, t_tools *tools);
bool						add_list(t_simple_cmds **list, t_simple_cmds *new,
								t_tools *tools);
void						grouping_cmd(int arg_size, char **str,
								t_parser_tools *parser_tools);
t_simple_cmds				*creat_ast(t_parser_tools *parser_tools);
t_parser_tools				init_parser_tools(t_tools *tools);
t_simple_cmds				*create_a_node(t_tools *tools);

#endif
