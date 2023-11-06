# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: toshota <toshota@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/26 19:52:48 by toshota           #+#    #+#              #
#    Updated: 2023/11/06 17:34:06 by toshota          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	pipex
CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
AR				=	ar rc
RM				=	rm -f
LIBFT_DIR		=	../../libft/

SRCS_DIR		=	src/
SRCS_FILES		=	check_arg.c check_func1.c check_func2.c \
					end_pipex.c get_cmd_absolute_path.c \
					get_cmd_absolute_path_utils.c get_pipex_data.c \
					get_file.c get_utils.c here_doc.c is_utils.c \
					pipex.c do_pipe.c utils1.c utils2.c is_specified_file.c

SRCS			=	$(addprefix $(SRCS_DIR), $(SRCS_FILES))
OBJS			=	$(SRCS:.c=.o)



all:		$(NAME)

$(NAME):	$(OBJS) Makefile
	@ make -C $(LIBFT_DIR)
	@ $(CC) $(CFLAGS) $(LIBFT_DIR)libft.a -I ../../libft/inc/ -I ../../inc/ $(OBJS) -o $(NAME)
	@ echo "compile to create an executable file: ./pipex"

bonus:		all

.c.o:		$(OBJS)
	@ $(CC) $(CFLAGS) -I ../../libft/inc/ -I ../../inc/ -c $< -o $@

clean:
	@ make clean -C $(LIBFT_DIR)
	@ $(RM) $(OBJS)
	@ echo "clean"

fclean:
	@ make fclean -C $(LIBFT_DIR)
	@ $(RM) $(OBJS)
	@ $(RM) $(NAME) $(B_NAME)
	@ echo "fclean"

re:			fclean all

.PHONY:		all bonus clean fclean re
