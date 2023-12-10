/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:34:46 by toshota           #+#    #+#             */
/*   Updated: 2023/12/10 21:52:00 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "builtin.h"
# include "define.h"
# include "libft.h"
# include "parser.h"
# include "pipex.h"
# include "expander.h"
# include <termios.h>
# include <signal.h>
# include <stdio.h>

// main.cに定義されている関数．本来はminishell.hでないヘッダーで宣言したい
int	process_input(t_tools *tools);

char	*delete_quotes(char *str, char c);
char	*detect_dollar(char *str, char **envp);

#endif
