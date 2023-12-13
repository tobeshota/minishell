NAME			=	minishell
CC				=	cc -g
# CC				=	cc -g -fsanitize=address
# CFLAGS			=	-Wall -Wextra -Werror
RM				=	rm -rf
LIBFT_DIR		=   libft/
LIBS			=	libft/libft.a
INCS			=	-I inc/ -I libft/inc/ -I$(shell brew --prefix readline)/include -g
SRCS_DIR		=	srcs/
OBJS_DIR		=	objs/

# echo srcs/**/*.c
SRCS		=	srcs/main.c srcs/pipex/array_node.c srcs/pipex/check_func1.c srcs/pipex/check_func2.c srcs/pipex/check_func3.c srcs/pipex/cp_argv.c srcs/pipex/do_loop_pipex.c srcs/pipex/do_pipex.c srcs/pipex/end_loop_pipex.c srcs/pipex/end_pipex.c srcs/pipex/get_cmd_absolute_path.c srcs/pipex/get_cmd_absolute_path_utils.c srcs/pipex/get_cmd_arg_fd.c srcs/pipex/get_cmd_count.c srcs/pipex/get_fd.c srcs/pipex/get_loop_pipex.c srcs/pipex/get_pipex.c srcs/pipex/get_splitted_argv.c srcs/pipex/get_splitter.c srcs/pipex/here_doc.c srcs/pipex/is_cmd.c srcs/pipex/is_file_ok.c srcs/pipex/is_specified_control_operators.c srcs/pipex/is_specified_file.c srcs/pipex/is_utils.c srcs/pipex/loop_pipex_utils.c srcs/pipex/loop_pipex.c srcs/pipex/node_utils1.c srcs/pipex/node_utils2.c srcs/pipex/omit.c srcs/pipex/pipex.c srcs/pipex/put_error.c srcs/pipex/reset_pipex.c srcs/pipex/set_fd.c srcs/pipex/utils1.c srcs/pipex/utils2.c srcs/builtin/cd.c srcs/builtin/echo.c srcs/builtin/env.c srcs/builtin/exec_builtin.c srcs/builtin/exit.c srcs/builtin/exec_export/add_new_value.c srcs/builtin/exec_export/export.c srcs/builtin/exec_export/get_old_env_to_be_updated.c srcs/builtin/exec_export/show_env.c srcs/builtin/exec_export/update_value.c srcs/builtin/pwd.c srcs/builtin/unset.c srcs/lexer/lexer.c srcs/lexer/word_in_node.c srcs/lexer/lexer_utils.c srcs/lexer/handle_token.c srcs/parser/parser.c srcs/parser/parser_utils.c srcs/parser/grouping_redirections.c srcs/parser/about_error.c srcs/expander/expander.c srcs/expander/expander_utils.c srcs/expander/expander_utils2.c srcs/signal.c srcs/main_utils.c srcs/parser/change_to_array.c

# echo srcs/pipex/**/*.c
# echo srcs/builtin/exec_export/*.c
# echo srcs/builtin/*.c
# echo srcs/expander/*.c
# SRCS		=	srcs/main.c srcs/pipex/array_node.c srcs/pipex/check_func1.c srcs/pipex/check_func2.c srcs/pipex/check_func3.c srcs/pipex/cp_argv.c srcs/pipex/do_loop_pipex.c srcs/pipex/do_pipex.c srcs/pipex/end_loop_pipex.c srcs/pipex/end_pipex.c srcs/pipex/get_cmd_absolute_path.c srcs/pipex/get_cmd_absolute_path_utils.c srcs/pipex/get_cmd_arg_fd.c srcs/pipex/get_cmd_count.c srcs/pipex/get_fd.c srcs/pipex/get_loop_pipex.c srcs/pipex/get_pipex.c srcs/pipex/get_splitted_argv.c srcs/pipex/get_splitter.c srcs/pipex/here_doc.c srcs/pipex/is_cmd.c srcs/pipex/is_file_ok.c srcs/pipex/is_specified_control_operators.c srcs/pipex/is_specified_file.c srcs/pipex/is_utils.c srcs/pipex/loop_pipex.c srcs/pipex/loop_pipex_utils.c srcs/pipex/node_utils1.c srcs/pipex/node_utils2.c srcs/pipex/omit.c srcs/pipex/pipex.c srcs/pipex/put_error.c srcs/pipex/reset_pipex.c srcs/pipex/set_fd.c srcs/pipex/utils1.c srcs/pipex/utils2.c srcs/builtin/exec_export/add_new_value.c srcs/builtin/exec_export/export.c srcs/builtin/exec_export/get_old_env_to_be_updated.c srcs/builtin/exec_export/show_env.c srcs/builtin/exec_export/update_value.c srcs/builtin/cd.c srcs/builtin/echo.c srcs/builtin/env.c srcs/builtin/exec_builtin.c srcs/builtin/exit.c srcs/builtin/pwd.c srcs/builtin/unset.c srcs/expander/expander.c srcs/expander/expander_utils.c srcs/expander/expander_utils2.c



OBJS		=	$(patsubst $(SRCS_DIR)%.c, $(OBJS_DIR)%.o, $(SRCS))



all:		$(NAME)

$(NAME):	$(OBJS) Makefile
	@ make bonus -C $(LIBFT_DIR)
	@ $(CC) $(CFLAGS) -lreadline -L$(shell brew --prefix readline)/lib $(LIBS) $(INCS) $(OBJS) -o $@
	@ echo "compile to create an executable file: ./$@"

bonus:		all

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	@ mkdir -p $(@D)
	@ $(CC) $(CFLAGS) $(INCS) -c $< -o $@

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
