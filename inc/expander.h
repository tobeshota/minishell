/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:18:00 by yoshimurahi       #+#    #+#             */
/*   Updated: 2023/12/19 13:45:46 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "define.h"
# include "minishell.h"
# include "parser.h"
# include <dirent.h>
# define IN_READLINE 0
# define IF_HEREDOC 2
# define IN_CMD 1
# define SIG_INT_COMING 130
# define HEREDOC_PARENT_CASE 3

int			handle_digit_after_dollar(int j, char *str);
char		**expander(t_tools *tools, char **str, char **envp);
size_t		dollar_sign(char *str);
char		*char_to_str(char c);
int			after_dol_lenght(char *str, int j);
size_t		find_equal(char *str);
size_t		find_dollar(char *str);
int			loop_if_dollar_sign(char **envp, char *str, char **tmp, int j);
int			question_mark(char **tmp, t_tools *tools);
char		*detect_dollar(char *str, char **envp, t_tools *tools);
int			handle_digit_after_dollar(int j, char *str);
bool		title(char *str, int j);
int			strlen_between_c(char *str, char c);

// expand_wildcard
void		expand_wildcard(char **h_argv);
bool		is_specified_wildcard(char *str);
void		expand_argv_w_wildcard(char **argv_to_be_updated);

//main_utils
bool		ft_simple_cmdsclear(t_simple_cmds **lst);
void		ft_lexerclear(t_lexer **lst);
int			free_tools(t_tools *tools);
int			implement_tools(t_tools *tools);
int			count_quotes(char *line);

//グローバル変数(終了ステータス)
void		signal_init_main(void);
void		sigquit_handler(int sig);
void		sigint_handler(int sig);

#endif
