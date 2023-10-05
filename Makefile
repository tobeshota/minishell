# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cjia <cjia@student.42tokyo.jp>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/26 19:52:48 by toshota           #+#    #+#              #
#    Updated: 2023/10/05 13:27:22 by cjia             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror
RM		=	rm -f
LIBFT	=   libft/
LIBS	=	libft/libft.a
INCS	=	minishell.h
SRCS	=	main.c
OBJS	=	$(SRCS:.c=.o)

$(NAME):	$(OBJS)
	@ make -C $(LIBFT)
	@ $(CC) $(CFLAGS) -o $(NAME) $(OBJS)

all:		$(NAME)

.c.o:		$(OBJS)
	@ $(CC) $(CFLAGS) -I $(INCS) -c $< -o $@

clean:
	@ make clean -C $(LIBFT)
	@ $(RM) $(OBJS)

fclean:		clean
	@ make fclean -C $(LIBFT)
	@ $(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
