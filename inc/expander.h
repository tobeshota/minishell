/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:18:00 by yoshimurahi       #+#    #+#             */
/*   Updated: 2023/12/28 17:30:39 by toshota          ###   ########.fr       */
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

int		handle_digit_after_dollar(int j, char *str);
char	**expander(t_tools *tools, char **str, char **envp);
size_t	dollar_sign(char *str);
char	*char_to_str(char c);
int		after_dol_lenght(char *str, int j);
size_t	find_equal(char *str);
size_t	find_dollar(char *str);
int		loop_if_dollar_sign(char **envp, char *str, char **tmp, int j);
int		question_mark(char **tmp, t_tools *tools);
char	*process_dollar_quote(char *str, char **envp, t_tools *tools);
int		handle_digit_after_dollar(int j, char *str);
bool	check_conditions(char *str, int j);
int		strlen_between_c(char *str, char c);
bool	last_quote(char *str, int *i, char c);
bool	first_quote(char *str, int *i, char c);
char	*add_ith_c(char *str, char add, int ith);
char	*omit_ith_c(char *str, int ith);
bool	search_space_quote_incre(char *str, int *i, char c);
bool	search_space_quote_decre(char *str, int *i, char c);
char	*move_to_last(char *str, char c, char opp);
char	*move_to_first(char *str, char c, char opp);
void	init_move_to_last(int *i, int *frags, int *opp_quote_frags);
char	*add_single_quote(char *str, int *j, int num, char **tmp);
void	add_double_auote_frag0(char *str, int *j, char **tmp, int *frags);
void	add_double_auote_frag1(char *str, int *j, char **tmp, int *frags);
void	handle_double_quotes(char **tmp, char *str, int *j, int *frags);
void	handle_single_quotes(char **tmp, char *str, int *j, int *frags);
void	judge_opp_frag(char *str, int opp, int *opp_quote_frags, int *i);
int		str_to_tmp(char **tmp, char *str);
int		char_to_tmp(char **tmp, char c);

// expand_wildcard
void	expand_wildcard(char **h_argv);
bool	is_specified_wildcard(char *str);
void	expand_argv_w_wildcard(char **argv_to_be_updated);

// main_utils
bool	ft_simple_cmdsclear(t_simple_cmds **lst);
void	ft_lexerclear(t_lexer **lst);
int		free_tools(t_tools *tools);
int		implement_tools(t_tools *tools);
int		count_quotes(char *line);

// about signal
void	signal_init_main(void);
void	sigquit_handler(int sig);
void	sigint_handler(int sig);

#endif
