# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agrotzsc <agrotzsc@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/01 03:58:29 by agrotzsc          #+#    #+#              #
#    Updated: 2022/04/21 11:45:35 by agrotzsc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#---- Config ------------------------------------------------------------------#

DEBUG ?= 0
ifeq ($(DEBUG), 1)
    CFLAGS 		=	-g -ggdb -Wall -Wextra -Werror
else
	CFLAGS		=	-Wall -Wextra -Werror
endif

NAME			=	libft.a
CC				=	gcc
DEF_COLOR		=	\033[0;39m
GREEN			=	\033[0;92m
YELLOW			=	\033[0;93m
RM				=	rm -rf

#---- Directorys --------------------------------------------------------------#

SRC_DIR			=	src/
OBJ_DIR			=	./obj/

#---- Files -------------------------------------------------------------------#

SRC_FILES		=	ft_memset.c			\
					ft_bzero.c			\
					ft_memcpy.c			\
					ft_memmove.c		\
					ft_memchr.c			\
					ft_memcmp.c			\
					ft_memcpy.c			\
					ft_strchr.c			\
					ft_strdup.c			\
					ft_strlcat.c		\
					ft_strlcpy.c		\
					ft_strlen.c			\
					ft_strmapi.c		\
					ft_strncmp.c		\
					ft_strrchr.c		\
					ft_strdelendchr.c	\
					ft_isalpha.c 		\
					ft_isalnum.c		\
					ft_isascii.c		\
					ft_isdigit.c		\
					ft_isprint.c		\
					ft_toupper.c		\
					ft_tolower.c		\
					ft_atoi.c			\
					ft_itoa.c			\
					ft_calloc.c			\
					ft_putchar_fd.c		\
					ft_putendl_fd.c		\
					ft_putnbr_fd.c		\
					ft_putstr_fd.c		\
					ft_striteri.c		\
					ft_strnstr.c		\
					ft_substr.c			\
					ft_strjoin.c		\
					ft_strtrim.c		\
					ft_split.c			\
					ft_strmapi.c		\
					ft_lstadd_back.c	\
					ft_lstadd_front.c	\
					ft_lstclear.c		\
					ft_lstdelone.c		\
					ft_lstiter.c		\
					ft_lstlast.c		\
					ft_lstmap.c			\
					ft_lstnew.c			\
					ft_lstsize.c

#---- Prefix ------------------------------------------------------------------#

OBJ_FILES		=	${SRC_FILES:.c=.o}
OBJ				=	$(addprefix $(OBJ_DIR),$(OBJ_FILES))

$(NAME): $(OBJ)
	@printf "%b" "\r\033[2K"
	@printf "%b" "\r$(YELLOW)Compiling: $(NAME)$(DEF_COLOR)"
	@$(AR) -rcs $(NAME) $?
	@printf "%b" "\r\033[2K"
	@printf "%b" "\r$(GREEN)$(NAME) compiled.$(DEF_COLOR)\n"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@printf "%b" "\r\033[2K"
	@printf "%b" "\r$(YELLOW)Compiling: $<$(DEF_COLOR)"
	@$(CC) $(CFLAGS) -o $@ -c $<

all: ${NAME}

clean:
	@${RM} ${OBJ_DIR}
	@echo "$(GREEN)$(NAME) Clean.$(DEF_COLOR)"
fclean: clean
	@${RM} ${NAME}
	@echo "$(GREEN)$(NAME) FClean.$(DEF_COLOR)"

re: fclean all