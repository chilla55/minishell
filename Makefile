# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/16 12:45:02 by skorte            #+#    #+#              #
#    Updated: 2022/04/23 22:09:25 by skorte           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror

SOURCES = 	minishell.c

OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS) libft
	$(CC) $(CFLAGS) -o $@ $< -L libft -l ft -L/usr/local/opt/readline/lib -lreadline

libft:
	make --directory=libft

clean:
	rm -f $(OBJECTS)
	rm -f minishell.h.gch
	make --directory=libft clean
	
fclean: clean
	rm -f minishell libft/libft.a

re: fclean all

.PHONY: all libft clean fclean re