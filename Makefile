# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/26 19:52:48 by toshota           #+#    #+#              #
#    Updated: 2023/11/18 01:43:23 by toshota          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell
CC				=	cc
#  -fsanitize=address
CFLAGS			=	-Wall -Wextra -Werror -g
RM				=	rm -rf
LIBFT_DIR		=   libft/
LIBS			=	libft/libft.a
INCS			=	-I inc/ -I libft/inc/
SRCS_DIR		=	srcs/
OBJS_DIR		=	objs/

# echo srcs/**/*.c
# echo srcs/pipex/src/*.c
SRCS		=	srcs/main.c srcs/pipex/src/check_func1.c srcs/pipex/src/check_func2.c srcs/pipex/src/do_pipe.c srcs/pipex/src/end_pipex.c srcs/pipex/src/get_cmd_absolute_path.c srcs/pipex/src/get_cmd_absolute_path_utils.c srcs/pipex/src/get_fd.c srcs/pipex/src/get_pipex_data.c srcs/pipex/src/get_utils.c srcs/pipex/src/here_doc.c srcs/pipex/src/is_file_ok.c srcs/pipex/src/is_specified_control_operators.c srcs/pipex/src/is_specified_file.c srcs/pipex/src/is_utils.c srcs/pipex/src/pipex.c srcs/pipex/src/utils1.c srcs/pipex/src/utils2.c

OBJS		=	$(patsubst $(SRCS_DIR)%.c, $(OBJS_DIR)%.o, $(SRCS))



all:		$(NAME)

$(NAME):	$(OBJS) Makefile
	@ make bonus -C $(LIBFT_DIR)
	@ $(CC) $(CFLAGS) $(LIBS) $(INCS) $(OBJS) -o $@
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
