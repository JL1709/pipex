# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: julian <julian@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/22 09:51:20 by jludt             #+#    #+#              #
#    Updated: 2021/08/19 16:38:26 by julian           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

MANDATORY = ft_split.c \
			ft_strchr.c \
			ft_strdup.c \
			ft_strjoin.c \
			ft_strlen.c \
			ft_strtrim.c \
			ft_substr.c

all: $(NAME)

$(NAME):
	gcc -c -Wall -Wextra -Werror *.c
	ar cr $(NAME) *.o

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re : fclean all

.PHONY: clean fclean re
