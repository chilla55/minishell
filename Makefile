# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/16 12:45:02 by skorte            #+#    #+#              #
#    Updated: 2022/04/25 09:18:59 by skorte           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror

SOURCES = 	minishell.c \
			msh_envp.c \
			msh_execve.c \

OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(OBJECTS):$(SOURCES)
	$(CC) $(CFLAGS) -c $(SOURCES)

$(NAME): $(OBJECTS) libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) -L libft -l ft -L/usr/local/opt/readline/lib -lreadline

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