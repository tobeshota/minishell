# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/26 19:52:48 by toshota           #+#    #+#              #
#    Updated: 2023/10/31 15:54:14 by toshota          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell
CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror -g -fsanitize=address
RM				=	rm -rf
LIBFT_DIR		=   libft/
LIBS			=	libft/libft.a
INCS			=	-I inc/ -I libft/inc/
SRCS_DIR		=	srcs/
OBJS_DIR		=	objs/

# echo srcs/**/*.c
SRCS		=	srcs/main.c

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
