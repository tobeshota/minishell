/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjia <cjia@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:18:00 by yoshimurahi       #+#    #+#             */
/*   Updated: 2023/12/08 13:08:23 by cjia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "define.h"
# include "minishell.h"
# include "parser.h"

char		**expander(t_tools *tools, char **str);
size_t		dollar_sign(char *str);
char		*char_to_str(char c);
int			after_dol_lenght(char *str, int j);
size_t		quotes_lenght(char *str);
size_t		find_equal(char *str);
size_t		find_dollar(char *str);
int			loop_if_dollar_sign(t_tools *tools, char *str, char **tmp, int j);
int			question_mark(char **tmp);

//main_utils
char		**ft_arrdup(char **arr);
void		ft_simple_cmdsclear(t_simple_cmds **lst);
void		ft_lexerclear(t_lexer **lst);

int			free_tools(t_tools *tools);
int			implement_tools(t_tools *tools);

//グローバル変数(終了ステータス)
extern int	g_status;
void		signal_init(void);
void		sigquit_handler(int sig);
void		sigint_handler(int sig);

#endif
