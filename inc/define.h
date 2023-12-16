/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:12:10 by toshota           #+#    #+#             */
/*   Updated: 2023/12/16 21:32:25 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# include <dirent.h>
# include <errno.h>
# include <stdbool.h>

typedef enum e_file_type	t_file_type;
typedef struct s_file		t_file;
typedef struct s_parser		t_parser;
typedef struct s_env		t_env;

typedef enum s_tokens
{
	PIPE = 1,
	GREAT,
	GREAT_GREAT,
	LESS,
	LESS_LESS,
	SEMICOLON,
	AND_AND,
	OR_OR,
	NONE = 0,
}							t_tokens;

typedef struct s_lexer
{
	struct s_lexer			*next;
	struct s_lexer			*prev;
	char					*str;
	int						i;
	t_tokens				token;
}							t_lexer;

typedef struct s_tools
{
	char					*str;
	struct s_simple_cmds	*simple_cmds;
	t_lexer					*lexer_list;
	char					**tmp_array;
	int						error_num;
}							t_tools;

typedef struct s_parser_tools
{
	t_lexer					*lexer_list;
	t_lexer					*redirections;
	int						num_redirections;
	struct s_tools			*tools;
}							t_parser_tools;

typedef struct s_simple_cmds
{
	char					**str;
	int						num_redirections;
	t_lexer					*redirections;
	struct s_simple_cmds	*next;
	struct s_simple_cmds	*prev;
}							t_simple_cmds;

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

typedef struct s_pipex
{
	int						infile_fd;
	int						outfile_fd;
	char					**cmd_absolute_path;
	char					**cmd_absolute_path_with_parameter;
	char					**argv;
	int						**pipe_fd;
	int						*error_num;
}							t_pipex;

typedef struct s_env
{
	char					*content;
	int						order;
	t_env					*next;
	t_env					*prev;
}							t_env;

//signal
typedef struct s_global
{
	int						error_num;
}							t_global;

t_global					g_global;

extern int						in_cmd;


// color
# define BLACK "\x1b[30m"
# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN "\x1b[36m"
# define WHITE "\x1b[37m"
# define BOLD "\x1b[1m"
# define DEFAULT "\x1b[0m\x1b[39m"

// prompt
# define MINISHELL_PROMPT "\x1b[32mminishell $ \x1b[0m\x1b[39m"
# define HERE_DOC_PROMPT "> "

# define EXIT_MSG "exit\n"

#endif
