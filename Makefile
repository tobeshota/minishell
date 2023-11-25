# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/26 19:52:48 by toshota           #+#    #+#              #
#    Updated: 2023/11/25 15:38:07 by toshota          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell
CC				=	cc -g
#  -fsanitize=address
# CFLAGS			=	-Wall -Wextra -Werror
RM				=	rm -rf
LIBFT_DIR		=   libft/
LIBS			=	libft/libft.a
INCS			=	-I inc/ -I libft/inc/ -I$(shell brew --prefix readline)/include
SRCS_DIR		=	srcs/
OBJS_DIR		=	objs/

# echo srcs/**/*.c
# echo srcs/pipex/*.c
# echo srcs/builtin/*.c
SRCS		=	srcs/main.c srcs/pipex/array_node.c srcs/pipex/check_func1.c srcs/pipex/check_func2.c srcs/pipex/do_pipe.c srcs/pipex/end_pipex.c srcs/pipex/get_cmd_absolute_path.c srcs/pipex/get_cmd_absolute_path_utils.c srcs/pipex/get_fd.c srcs/pipex/get_pipex_data.c srcs/pipex/get_utils.c srcs/pipex/here_doc.c srcs/pipex/is_file_ok.c srcs/pipex/is_specified_control_operators.c srcs/pipex/is_specified_file.c srcs/pipex/is_utils.c  srcs/pipex/node_utils1.c srcs/pipex/node_utils2.c srcs/pipex/pipex.c srcs/pipex/set_fd.c srcs/pipex/utils1.c srcs/pipex/utils2.c srcs/builtin/cd.c srcs/builtin/echo.c srcs/builtin/env.c srcs/builtin/exec_builtin.c srcs/builtin/exit.c srcs/builtin/export.c srcs/builtin/pwd.c srcs/builtin/unset.c

OBJS		=	$(patsubst $(SRCS_DIR)%.c, $(OBJS_DIR)%.o, $(SRCS))



all:		$(NAME)

$(NAME):	$(OBJS) Makefile
	@ make bonus -C $(LIBFT_DIR)
	@ $(CC) $(CFLAGS) -lreadline -L$(shell brew --prefix readline)/lib $(LIBS) $(INCS) $(OBJS) -o $@
	@ echo "compile to create an executable file: ./$@"

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
