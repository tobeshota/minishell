/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:34:46 by toshota           #+#    #+#             */
/*   Updated: 2023/10/31 12:34:46 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libc.h>

typedef enum e_file_type	t_file_type;
typedef struct s_file		t_file;
typedef struct s_parser		t_parser;

typedef enum e_file_type
{
	HEREDOC,
	INPUT,
	APPEND,
	OUTPUT
}							t_file_type;

typedef struct s_file
{
	char					*file_name;
	t_file_type				file_type;
	t_file					*next;
}							t_file;

typedef struct s_parser
{
	char					**line;
	t_file					*files;
	t_parser				*next;
	t_parser				*prev;
}							t_parser;

#endif
