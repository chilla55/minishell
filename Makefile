# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/16 12:45:02 by skorte            #+#    #+#              #
#    Updated: 2022/04/21 10:32:06 by skorte           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror

SOURCES = minishell.c

OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS) libft
	$(CC) $(CFLAGS) -o $@ $< -L libft -l ft

libft:
	make --directory=libft

clean:
	rm -f $(OBJECTS)
	make --directory=libft clean
	
fclean: clean
	rm -f minishell libft/libft.a

re: fclean all

.PHONY: all libft clean fclean re