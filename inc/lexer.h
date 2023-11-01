/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshimurahiro <yoshimurahiro@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 13:37:16 by yoshimurahi       #+#    #+#             */
/*   Updated: 2023/11/01 09:54:43 by yoshimurahi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct		s_token
{
	char			*str;
	int				type;
	struct s_token	*next;
}					t_token;

typedef struct s_lexer
{
    struct s_lexer	*next;
	struct s_lexer	*prev;
    char			*str;
	t_token 		token_head;
}   t_lexer;

typedef struct s_tentative 
{
    char                    *str;
    char					**envp;
    t_lexer					*lexer_list;
    
}   t_tentative;

typedef enum s_tokens
{
	PIPE = 1,
	GREAT,
	GREAT_GREAT,
	LESS,
	LESS_LESS,
	NONE = 0,
}	t_tokens;

#endif