# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: julian <julian@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/22 09:51:20 by jludt             #+#    #+#              #
#    Updated: 2021/10/04 18:22:41 by julian           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

MANDATORY = ft_putstr_fd.c	\
			ft_split.c		\
			ft_strcmp.c		\
			ft_strncmp.c	\
			ft_strchr.c		\
			ft_strdup.c		\
			ft_strjoin.c	\
			ft_strjoin2.c	\
			ft_strlen.c		\
			ft_strtrim.c	\
			ft_substr.c		\
			get_next_line.c	\

all: $(NAME)

$(NAME):
	@gcc -c -Wall -Wextra -Werror *.c
	@ar cr $(NAME) *.o

clean:
	@rm -f *.o

fclean: clean
	@rm -f $(NAME)

re : fclean all

.PHONY: clean fclean re
