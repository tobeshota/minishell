/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:12:10 by toshota           #+#    #+#             */
/*   Updated: 2023/11/18 00:58:25 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

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

typedef struct s_pipex_data
{
	int		infile_fd;
	int		outfile_fd;
	char	**cmd_absolute_path;
	char	**cmd_absolute_path_with_parameter;
	int		**pipe_fd;
}			t_pipex_data;


// color
#define BLACK	"\x1b[30m"
#define RED		"\x1b[31m"
#define GREEN	"\x1b[32m"
#define YELLOW	"\x1b[33m"
#define BLUE	"\x1b[34m"
#define MAGENTA	"\x1b[35m"
#define CYAN	"\x1b[36m"
#define WHITE	"\x1b[37m"
#define BOLD	"\x1b[1m"
#define DEFAULT	"\x1b[0m\x1b[39m"

#endif
