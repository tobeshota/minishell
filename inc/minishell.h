/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:34:46 by toshota           #+#    #+#             */
/*   Updated: 2023/12/19 13:52:41 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "builtin.h"
# include "define.h"
# include "expander.h"
# include "libft.h"
# include "parser.h"
# include "pipex.h"
# include <signal.h>
# include <stdio.h>
# include <termios.h>

void	init_minishell(char **envp, t_env **env);
int		handle_input(t_tools *tools, t_env **env);

#endif
