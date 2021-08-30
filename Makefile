# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: julian <julian@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/11 12:13:12 by jludt             #+#    #+#              #
#    Updated: 2021/08/30 17:24:01 by julian           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = gcc

LIBFTPATH = ./libft/libft.a

CFLAGS = -Wall -Werror -Wextra $(LIBFTPATH)

CFILES =	pipex.c \
			utils/exit.c \
			utils/manage_error.c \
			utils/get_path.c \
			utils/processes.c

OBJECTS = $(CFILES:.c=.o)

$(NAME):
	make --directory=./libft
	$(CC) $(CFILES) $(CFLAGS) -o $(NAME)

clean: 
	rm -f $(OBJECTS)
	make clean --directory=./libft

fclean:
	rm -f $(NAME) $(OBJECTS)
	make fclean --directory=./libft

re: fclean $(NAME)
	make re --directory=./libft
