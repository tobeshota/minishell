#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"

#define	EXIT_FAILURE	1
#define	EXIT_SUCCESS	0


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
}	t_tokens;

typedef struct s_lexer
{
    struct s_lexer	*next;
	struct s_lexer	*prev;
    char			*str;
	int				i;
	t_tokens 		token;
}   t_lexer;

typedef struct s_tools
{
    char                    *str;
	struct s_simple_cmds	*simple_cmds;
    t_lexer					*lexer_list;
	char 					**envp;
	char 					**tmp_array;
}   t_tools;


typedef struct s_parser_tools
{
	t_lexer			*lexer_list;
	t_lexer			*redirections;
	int				num_redirections;
	struct s_tools	*tools;
}	t_parser_tools;

typedef struct s_simple_cmds
{
	char					**str;
	int						num_redirections;
	t_lexer					*redirections;
	struct s_simple_cmds	*next;
	struct s_simple_cmds	*prev;
}	t_simple_cmds;


//about lexer
int lexer(t_tools *lexer_tools);
int handle_token(char *str, int i, t_lexer **lexer_list);
int word_in_node(char *str, int i, t_lexer **lexer_list);
int get_token_type(char *str, int i);
int add_node(char *str,  t_tokens token, t_lexer **lexer_list);
void print_lexer(t_lexer *lexer_list);
void	add_back_node(t_lexer **lexer_list, t_lexer *node);
t_lexer	*make_node(char *str, int token);
int check_token(char *str, int i);
void free_lexer(t_lexer *lexer);


//about parser
int		parser(t_tools *tools);
void erase_token(t_lexer **lexer_list, int i);
int	count_args(t_lexer *lexer_list);
t_simple_cmds	*recreated_node(char **str, int num_redirections, t_lexer *redirections);
int		grouping_redirections(t_parser_tools *parser_tools);
void	parser_error(int error, t_lexer *lexer_list);
int	parser_token_error(t_tools *tools, t_lexer *lexer_list,
	t_tokens token);
int	handle_operator_error(t_tools *tools, t_tokens token);
char **change_to_array(t_tools *tools);
int	ft_error(int error);




#endif
