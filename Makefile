NAME			=	minishell
CC				=	cc -g
# CC				=	cc -g -fsanitize=address
CFLAGS			=	-Wall -Wextra -Werror
RM				=	rm -rf
LIBFT_DIR		=   libft/
LIBS			=	libft/libft.a
INCS			=	-I inc/ -I libft/inc/ -I$(shell brew --prefix readline)/include -g
SRCS_DIR		=	srcs/
OBJS_DIR		=	objs/

# echo srcs/**/*.c
SRCS		=	srcs/main/main.c srcs/main/main_utils1.c srcs/main/main_utils2.c srcs/main/signal.c srcs/expander/add_quotes.c srcs/expander/conditions_func.c srcs/expander/detect_dollar_utils.c srcs/expander/expand_wildcard/expand_wildcard.c srcs/expander/expand_wildcard/expand_wildcard_utils1.c srcs/expander/expand_wildcard/expand_wildcard_utils2.c srcs/expander/expander.c srcs/expander/expander_utils.c srcs/expander/process_dollar_quote.c srcs/expander/trim_quotes.c srcs/expander/trim_quotes_utils.c srcs/lexer/handle_token.c srcs/lexer/lexer.c srcs/lexer/lexer_utils.c srcs/lexer/word_in_node.c srcs/parser/about_error.c srcs/parser/change_to_array.c srcs/parser/change_to_array_utils.c srcs/parser/grouping_redirections.c srcs/parser/parser.c srcs/parser/parser_utils.c srcs/parser/parser_utils2.c srcs/builtin/cd.c srcs/builtin/echo.c srcs/builtin/env.c srcs/builtin/exec_builtin/exec_builtin.c srcs/builtin/exec_builtin/split_str_according_to_encloser.c srcs/builtin/exec_builtin/split_str_according_to_splitter.c srcs/builtin/exec_builtin/split_wo_enclosed_str.c srcs/builtin/exec_exit/exit.c srcs/builtin/exec_exit/exit_utils.c srcs/builtin/exec_export/add_new_value.c srcs/builtin/exec_export/export.c srcs/builtin/exec_export/get_old_env_to_be_updated.c srcs/builtin/exec_export/show_env.c srcs/builtin/exec_export/update_value.c srcs/builtin/pwd.c srcs/builtin/unset.c srcs/pipex/get/cmd_absolute_path/get_cmd_absolute_path.c srcs/pipex/get/cmd_absolute_path/get_cmd_arg_fd.c srcs/pipex/get/cmd_absolute_path/get_cmd_count.c srcs/pipex/get/iofd/get_fd.c srcs/pipex/get/iofd/here_doc.c srcs/pipex/get/iofd/set_fd.c srcs/pipex/get/other/get_child.c srcs/pipex/get/other/get_pipe.c srcs/pipex/get/other/get_splitted_argv.c srcs/pipex/get/other/get_splitter.c srcs/pipex/loop/do_loop_pipex.c srcs/pipex/loop/end_loop_pipex.c srcs/pipex/loop/get_loop_pipex.c srcs/pipex/loop/loop_pipex.c srcs/pipex/pipex/do_pipex.c srcs/pipex/pipex/end_pipex.c srcs/pipex/pipex/get_pipex.c srcs/pipex/pipex/pipex.c srcs/pipex/utils/check/check_arg.c srcs/pipex/utils/check/check_func1.c srcs/pipex/utils/check/check_func2.c srcs/pipex/utils/check/check_func3.c srcs/pipex/utils/is/is_cmd.c srcs/pipex/utils/is/is_file_ok.c srcs/pipex/utils/is/is_specified_control_operators.c srcs/pipex/utils/is/is_specified_file.c srcs/pipex/utils/is/is_utils.c srcs/pipex/utils/node/array_node.c srcs/pipex/utils/node/node_utils1.c srcs/pipex/utils/node/node_utils2.c srcs/pipex/utils/node/node_utils3.c srcs/pipex/utils/node/node_utils4.c srcs/pipex/utils/other/cp_argv.c srcs/pipex/utils/other/do_pipex_utils.c srcs/pipex/utils/other/get_cmd_absolute_path_utils.c srcs/pipex/utils/other/loop_pipex_utils.c srcs/pipex/utils/other/omit.c srcs/pipex/utils/other/put_error.c srcs/pipex/utils/other/utils1.c srcs/pipex/utils/other/utils2.c srcs/pipex/utils/other/utils3.c


OBJS		=	$(patsubst $(SRCS_DIR)%.c, $(OBJS_DIR)%.o, $(SRCS))



all:		$(NAME)

$(NAME):	$(OBJS) Makefile
	@ make bonus -C $(LIBFT_DIR)
	@ $(CC) $(CFLAGS) -lreadline -L$(shell brew --prefix readline)/lib $(LIBS) $(INCS) $(OBJS) -o $@
	@ echo "compile to create an executable file: ./$@"

bonus:		all

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	@ mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

clean:
	@ make clean -C $(LIBFT_DIR)
	@ $(RM) $(OBJS_DIR)
	@ echo $@

fclean:
	@ make fclean -C $(LIBFT_DIR)
	@ $(RM) $(OBJS_DIR)
	@ $(RM) $(NAME)
	@ echo $@

re:			fclean all

.PHONY:		all clean fclean re
